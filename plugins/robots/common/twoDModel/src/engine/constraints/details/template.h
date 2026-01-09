/* Copyright 2025 CyberTech Labs Ltd.
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

#pragma once

#include <QHash>
#include <QString>
#include <QStringList>
#include <vector>
#include <QDomElement>

namespace twoDModel {
namespace constraints {
namespace details {

/*!
 * \class XmlTemplate
 * \brief A class that describes a template and stores information about its parameters, default substitution value,
 * substitution order, and more
 * \inmodule twoDModel::constraints::details
 *
 * General view of template declaration:
 * \code
 * <template name="my_template>
 *     <params>
 *         <!-- Default value as text -->
 *         <param name="nested_variable" default="var"/>
 *         <!-- Default value as xml node -->
 *         <param name="xml_node">
 *             <difference>
 *                 <int value="1"/>
 *                 <variableValue name=#{nested_variable}/>
 *             </difference>
 *         <!-- No default value-->
 *         <param name="value"/>
 *     </params>
 *     <content>
 * <![CDATA[
 *     <!-- I want use value param for sum in xml constraints language -->
 *     <sum>
 *         <variableValue name="#{value}"/>
 *         #{xml_node}
 *     </sum>
 * ]]>
 *     </content>
 * </template>
 *
 * \endcode
 * Thus, the substitution parameters can be text or valid xml nodes.
 * The order in which parameters are defined in a template determines the order in which they are initialized.
 * In the example above, the nestedVariable parameter can be used in the default value for the xml_node parameter.
 */
class XmlTemplate
{
public:
	XmlTemplate(const XmlTemplate&) = delete;
	XmlTemplate& operator=(const XmlTemplate&) = delete;
	XmlTemplate(XmlTemplate&&) noexcept = default;
	XmlTemplate& operator=(XmlTemplate&&) noexcept = default;
	virtual ~XmlTemplate() = default;

	/// A constructor that accepts the template name.
	/// At the moment, the name of the template must be unique throughout the project, there is no namespace,
	/// and when the user redefines the library template, an appropriate warning will be issued.
	explicit XmlTemplate(QString id) noexcept;

	/// It parses the template definition by collecting information about the order in which parameters are
	/// defined and their default values. Performs optional checks for the template body to improve diagnostics.
	void processDeclaration(const QDomElement &templateDeclaration);

	/// Returns errors received during the parsing of the template definition, which can later be displayed
	/// to the user from the ConsoleReporterInterface or recorded in logs.
	QStringList declarationErrors() const;

	/// It is used to insert parameters into the template body. The parameters are inserted in the reverse order
	/// relative to initialization, which means that the parameters declared earlier can be used
	/// in the parameters declared later.
	QString substitute(const QDomElement &templateUsage);

	/// Returns errors received when substituting template parameters, which can later be displayed
	/// to the user from the ConsoleReporter interface or recorded in logs.
	QStringList substitutionErrors() const;

	enum class TemplateParseErrorCode {
		ContentFormatNotSuppoted,
		UseSpecialSyntaxForUndeclaredParam,
		ParamsTagContainOnlyParam,
		MissingParamNameAttribute,
		MissingContentTag,
		MissingTemplateNameAttribute,
		RedefinitionExistingTemplate,
		TemplatesTagContaintsOnlyTemplate,
		TemplateLibraryNotFound,
		QtXmlParserError
	};

	enum class TemplateSubstitutionErrorCode {
		UseUndeclaredParam,
		UseTagContainsOnlyWithTag,
		MissingReqiuredParam,
		UseTagContainsTemplateAttr,
		RecursiveTemplateExpansion,
		UseUndeclaredTemplate,
		QtXmlParserError
	};

protected:
	virtual void addDeclarationError(const QString& message, int lineNumber, TemplateParseErrorCode code);
	virtual void addSubstitutionError(const QString& message, int lineNumber, TemplateSubstitutionErrorCode code);
private:
	/// Parses template parameters, checking their compliance with template grammar,
	/// correct use of default values, and initializes parameters
	void processParams(const QDomElement &params);

	/// Parses the body of the template
	void processContent(const QDomElement &content);

	/// Parses the with tag of the template language. As a rule, parameters can be located in multiple with
	/// tags at the user's discretion, and multiple definitions of the same parameter will use the last definition
	/// in the case of an xml parameter value as an xml node, and any of the values if the parameter is an attribute
	/// (the xml specification does not specify the order of attributes)
	void parseWith(const QDomElement &with, QHash<QString, QString> &paramsForReplace);

	bool validateParam(const QDomNode &with, const QString &param);
	void parseParams(const QDomElement &paramTag, QHash<QString, QString>
			 &paramsForReplace, bool fromTemplate = false);
	void substitute(const QString& name, const QString& value, QString &result);
	void clear();

	struct TemplateParamInfo {
		QString mName {};
		// The default value of parameter can be an empty string
		QString mDefaultValue {};
		// std::optional is a c++17 feature, but I don't want to write my own
		bool mHasDefaultValue {};

		TemplateParamInfo(
			QString parameterName,
			QString defaultValue,
			bool hasDefaultValue) noexcept
		    : mName(std::move(parameterName))
		    , mDefaultValue(std::move(defaultValue))
		    , mHasDefaultValue(hasDefaultValue) {}
	};


	QStringList mDeclarationErrors;
	QStringList mSubstitutionErrors;
	QString mId;
	QString mText;
	std::vector<QString> mOrder;
	QHash<QString, TemplateParamInfo> mParameters;
};

} // namespace details
} // namespace constraints
} // namespace twoDModel
