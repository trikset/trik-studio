/* Copyright 2026 CyberTech Labs Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include <stack>
#include "templatesProcessor.h"
#include "templatesManager.h"
#include "template.h"
#include <QObject>

using namespace twoDModel::templates::details;

TemplatesProcessor::TemplatesProcessor(details::TemplatesManager *manager) noexcept
	: mManager(manager){}

QDomElement TemplatesProcessor::processTemplate(const QDomElement &elements, ExpansionContext& context)
{
	auto &&templateName = elements.tagName() == "use" ? elements.attribute("template") : elements.tagName();

	if (templateName.isEmpty()) {
		error(QObject::tr(R"(The &lt;use&gt; tag must contain a "template" attribute)")
				, elements.lineNumber(), context, SubstitutionErrorCode::UseTagContainsTemplateAttr);
		return {};
	}

	if (context.mMacrosInProgress.contains(templateName)) {
		error(QObject::tr(
			"Recursive template expansion detected: %1 -> %2")
			.arg(context.mOrder.join(" -> "), templateName), elements.lineNumber(),
			context, SubstitutionErrorCode::RecursiveTemplateExpansion);
		return {};
	}

	auto *foundTemplate = mManager->findTemplate(templateName);

	if (!foundTemplate) {
		error(QObject::tr(
			"The &lt;use&gt; tag contains a template=%1"
			" attribute that is not the name of a declared template")
			.arg(templateName), elements.lineNumber(), context,
			SubstitutionErrorCode::UseUndeclaredTemplate);
		return {};
	}

	auto &xmlTemplate = *foundTemplate;
	auto substitutionResult = xmlTemplate.substitute(elements);
	const auto &errors = xmlTemplate.substitutionErrors();
	for (auto &&substitutionError: errors) {
		error(substitutionError.error, substitutionError.line,
					context, substitutionError.errorCode);
	}
	if (!errors.isEmpty()) {
		return {};
	}

	auto &&wrappedXml = QString("<root>%1</root>").arg(substitutionResult);
	QDomDocument result;
	QString errorMessage;
	int errorLine;
	const auto &message =
		QObject::tr("After substituting the parameters for"
			    " the template %1, it did not become a valid xml node").arg(templateName);
	if (!result.setContent(wrappedXml, &errorMessage, &errorLine)) {
		error(QString("%1 %2").arg(message, errorMessage), errorLine, context,
				SubstitutionErrorCode::QtXmlParserError);
		return {};
	}

	context.mOrder.append(templateName);
	context.mDepth++;
	context.mMacrosInProgress.insert(templateName);
	return result.documentElement();
}

bool TemplatesProcessor::substitute(const QDomElement& constraintsXml) {
	std::stack<ExpansionItem> elementStack;
	const auto &rootContext = ExpansionContext();
	auto&& child = constraintsXml.firstChildElement();

	while (!child.isNull()) {
		elementStack.push(ExpansionItem{child, rootContext.fork()});
		child = child.nextSiblingElement();
	}

	while (!elementStack.empty()) {
		auto currentItem = std::move(elementStack.top());
		auto&& current = currentItem.mElement;
		auto&& context = currentItem.mContext;

		elementStack.pop();

		// If the current node is not equal to use, we just want to process its children later.
		const auto isTemplate = current.tagName() == "use" || mManager->isPotentialTemplate(current.tagName());
		if (!isTemplate) {
			auto&& child = current.firstChildElement();
			while (!child.isNull()) {
				elementStack.push(ExpansionItem{child, context.fork()});
				child = child.nextSiblingElement();
			}
			continue;
		}

		// If it is a <use> node, we want to replace it with a template definition.
		auto&& currentContext = context.fork();
		auto&& replacement = processTemplate(current, currentContext);
		auto&& parent = current.parentNode().toElement();

		auto&& nextSibling = current.nextSibling();

		// If the substitution is unsuccessful, we do not process the subtree,
		// the user will see an error message.
		if (replacement.isNull()) {
			parent.removeChild(current);
			return false;
		}

		// Otherwise, we replace the use tag with a sequence of received nodes,
		// the last of these nodes must have the next node as the node being replaced.
		parent.removeChild(current);

		auto &&replChild = replacement.firstChildElement();
		std::vector<ExpansionItem> newlyInserted;

		while (!replChild.isNull()) {
			auto &&next = replChild.nextSiblingElement();
			auto &&cloned = replChild.toElement();
			if (nextSibling.isNull()) {
				parent.appendChild(cloned);
			} else {
				parent.insertBefore(cloned, nextSibling);
			}

			newlyInserted.push_back(ExpansionItem{cloned, currentContext});
			replChild = next;
		}

		for (auto it = newlyInserted.rbegin(); it != newlyInserted.rend(); ++it) {
			elementStack.push(*it);
		}
	}
	return true;
}


void TemplatesProcessor::clear()
{
	mErrors.clear();
}

QStringList TemplatesProcessor::errors() const
{
	return mErrors;
}

void TemplatesProcessor::error(const QString& message,
				      int line,
				      const ExpansionContext &context,
				      SubstitutionErrorCode code)
{
	Q_UNUSED(code)
	QStringList messages = {message, QObject::tr("line %1").arg(line)};
	const auto inTemplate = !context.mOrder.isEmpty();
	if (!inTemplate) {
		messages.append(QObject::tr("relative the beginning of the &lt;constraints&gt; tag"));
	} else {
		auto currentTemplateName = context.mOrder.last();
		messages.append(QObject::tr("relative to the beginning of the %1 template body")
				.arg(currentTemplateName));
	}
	const auto &finalMessage = messages.join(" ");
	mErrors << finalMessage;
	if (inTemplate) {
		const auto &substitutionChain = QObject::tr("Substitution chain: %1.")
				.arg(context.mOrder.join(" -> "));
		mErrors << substitutionChain;
	}
}

