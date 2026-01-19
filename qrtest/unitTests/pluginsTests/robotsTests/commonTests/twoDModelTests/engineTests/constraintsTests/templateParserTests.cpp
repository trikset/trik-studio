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

#include "templateParserTests.h"
#include <twoDModel/robotModel/xmlTemplateMock.h>
#include <QTimer>

using namespace qrTest::robotsTests::commonTwoDModelTests;
using namespace twoDModel::templates::details;

TEST_P(XmlTemplateErrorTest, EachErrorScenario) {
	const auto &testCase = GetParam();

	TemplateParseErrorCode actualCode;
	int actualLine;

	EXPECT_CALL(*mMockTemplate, addDeclarationError(::testing::_, ::testing::_, ::testing::_))
		.Times(1)
		.WillOnce(::testing::Invoke(
			[&](const QString&, int line, TemplateParseErrorCode code) {
				actualCode = code;
				actualLine = line;
		}
	));

	QDomDocument doc;
	doc.setContent(testCase.testXml);
	mMockTemplate->processDeclaration(doc.documentElement());

	EXPECT_EQ(actualCode, testCase.expectedCode);
	EXPECT_EQ(actualLine, testCase.expectedLine);
}

TEST_P(XmlTemplateParserErrorTest, ParserEachErrorScenario) {
	const auto &testCase = GetParam();

	TemplateParseErrorCode actualCode;
	int actualLine;

	EXPECT_CALL(*mMockTemplateParser, parseError(::testing::_, ::testing::_, ::testing::_, ::testing::_))
		.Times(1)
		.WillOnce(::testing::Invoke(
			[&](const QString&, int line, TemplateParseErrorCode code, const QString&) {
				actualCode = code;
				actualLine = line;
		}
	));

	QDomDocument doc;
	doc.setContent(testCase.testXml);
	mMockTemplateParser->parseTemplates(doc);

	EXPECT_EQ(actualCode, testCase.expectedCode);
	EXPECT_EQ(actualLine, testCase.expectedLine);
}

TEST_P(XmlTemplateSubstitutionErrorTest, SubstitutionEachErrorScenario) {
	const auto &testCase = GetParam();

	TemplateSubstitutionErrorCode actualCode;
	int actualLine;

	EXPECT_CALL(*mMockTemplate, mockAddSubstitutionError(::testing::_, ::testing::_, ::testing::_))
		.Times(1)
		.WillOnce(::testing::Invoke(
			[&](const QString&, int line, TemplateSubstitutionErrorCode code) {
				actualCode = code;
				actualLine = line;
		}
	));

	// template definition xml
	QDomDocument templateDefinitions;
	templateDefinitions.setContent(testCase.templatesDefinition);
	mMockTemplate->processDeclaration(templateDefinitions.documentElement());

	// Constraint xml
	QDomDocument doc;
	doc.setContent(testCase.testXml);
	mMockTemplate->substitute(doc.documentElement());

	EXPECT_EQ(actualCode, testCase.expectedCode);
	EXPECT_EQ(actualLine, testCase.expectedLine);
}

TEST_P(XmlTemplateParserSubstitutionErrorTest, SubstitutionPaserEachErrorScenario) {
	const auto &testCase = GetParam();

	TemplateSubstitutionErrorCode actualCode;
	int actualLine;

	EXPECT_CALL(*mMockTemplateParser, substituteError(::testing::_, ::testing::_, ::testing::_, ::testing::_))
		.Times(1)
		.WillOnce(::testing::Invoke(
			[&](const QString&, int line,
				const  qrTest::XmlTemplateParserMock::ExpansionContext &, TemplateSubstitutionErrorCode code) {
				actualCode = code;
				actualLine = line;
		}
	));

	// template definition xml
	QDomDocument templateDefinitions;
	templateDefinitions.setContent(testCase.templatesDefinition);
	mMockTemplateParser->parseTemplates(templateDefinitions);

	// Constraint xml
	QDomDocument doc;
	doc.setContent(testCase.testXml);
	mMockTemplateParser->substitute(doc.documentElement());

	EXPECT_EQ(actualCode, testCase.expectedCode);
	EXPECT_EQ(actualLine, testCase.expectedLine);
}

// clazy:excludeall=non-pod-global-static
const std::vector<ErrorTestCase> testCases = {
	{
		TemplateParseErrorCode::ContentFormatNotSuppoted,
		2, // Non expected content on line 3 relative first string of input document
R"(<template name="test_template">
	<content>
		<something-non-cdata-tag/>
	</content>
</template>
)",
		"ContentFormatNotSuppoted"
	},
	{
		TemplateParseErrorCode::UseSpecialSyntaxForUndeclaredParam,
		2,
R"(<template name="test_template">
	<content>
<![CDATA[
	<difference>
		<int value="5"/>
	<int value="12"/>
	</difference>
	#{use_spec_syntax_for_undecl_param_on_line_8}
]]>
	</content>
</template>
	)",
		"UseSpecialSyntaxForUndeclaredParam"
	},
	{
		TemplateParseErrorCode::ParamsTagContainOnlyParam,
		6, // <trigger> on line 6
R"(<template name="test_template">
<params>
	<param name="id"/>
	<param name="settedUpInit" default="true"/>
	<param name="trigger"/> <!-- typo, child tag is default param -->
	<trigger>
			<success/>
		</trigger>
	<param name="conditions">
		<condition>
			<true/>
		</condition>
	</param>
</params>
	<content>
<![CDATA[
	<difference>
		<int value="5"/>
	<int value="12"/>
	</difference>
]]>
	</content>
</template>
	)",
		"ParamsTagContainOnlyParam"
	},
	{
		TemplateParseErrorCode::MissingParamNameAttribute,
		5, // missing name on line
R"(<template name="test_template">
	<params>
		<param name="id"/>
		<param name="settedUpInit" default="true"/>
		<param>
			<condition>
				<true/>
			</condition>
		</param>
	</params>
	<content>
<![CDATA[
	<difference>
		<int value="5"/>
		<int value="12"/>
	</difference>
]]>
	</content>
</template>
	)",
		"MissingParamNameAttribute"
	},
	{
		TemplateParseErrorCode::MissingContentTag,
		3, // missing content tag for template on line 3
R"(

<template name="test_template">
	<params>
		<param name="id"/>
	</params>
</template>
	)",
		"MissingContentTag"
	},
};

const std::vector<ErrorTestCase> parserTestCases = {
	{
		TemplateParseErrorCode::MissingTemplateNameAttribute,
		3,
R"(
<templates>
<template name="">
	<content>
		<something-non-cdata-tag/>
	</content>
</template>
</templates>
)",
		"MissingTemplateNameAttribute"
	},
	{
		TemplateParseErrorCode::RedefinitionExistingTemplate,
		14,
R"(
<templates>
<template name="name">
	<content>
	<![CDATA[
		<difference>
			<int value="5"/>
			<int value="12"/>
		</difference>
	]]>
	</content>
</template>

<template name="name">
	<content>
	<![CDATA[
		<difference>
			<int value="5"/>
			<int value="12"/>
		</difference>
	]]>
	</content>
</template>

</templates>
)",
		"RedefenitionExistingTemplate"
	},
	{
		TemplateParseErrorCode::TemplatesTagContaintsOnlyTemplate,
		3,
R"(
<templates>
<bober name="name">
	<content>
	<![CDATA[
		<difference>
			<int value="5"/>
			<int value="12"/>
		</difference>
	]]>
	</content>
</template>

<template name="name">
	<content>
	<![CDATA[
		<difference>
			<int value="5"/>
			<int value="12"/>
		</difference>
	]]>
	</content>
</template>

</templates>
)",
		"TemplatesTagContaintsOnlyTemplate"
	},
};

const std::vector<SubstitutionErrorTestCase> substitutionTestCases = {
	{
		TemplateSubstitutionErrorCode::UseUndeclaredParam,
		3,
R"(
<template name="test_template">
	<content>
<![CDATA[
	<difference>
		<int value="5"/>
		<int value="12"/>
	</difference>
]]>
	</content>
</template>
)",
R"(
<use template="test_template">
	<with id="278"/> <!-- line 3 -->
</use>
)",
		"UseUndeclaredParam"
	},
	{
		TemplateSubstitutionErrorCode::UseTagContainsOnlyWithTag,
		4,
R"(
<template name="test_template">
<params>
	<param name="id"/>
</params>
	<content>
<![CDATA[
	<difference>
		<int value=#{id}"/>
		<int value="12"/>
	</difference>
]]>
	</content>
</template>
)",
R"(
<use template="test_template">
	<with id="278"/> <!-- valid use -->
	<strange-tag/>
</use>
)",
		"UseTagContainsOnlyWithTag"
	},
	{
		TemplateSubstitutionErrorCode::MissingReqiuredParam,
		2,
R"(
<template name="test_template">
<params>
	<param name="requiredParamWithoutDefaultValue"/>
</params>
	<content>
<![CDATA[
	#{xml_node}
]]>
	</content>
</template>
)",
R"(
<use template="test_template"/>
)",
		"MissingReqiuredParam"
	},
};

const std::vector<SubstitutionErrorTestCase> substitutionParserTestCases = {
	{
		TemplateSubstitutionErrorCode::UseTagContainsTemplateAttr,
		3,
R"(
<templates>
<template name="test_template">
	<content>
<![CDATA[
	<difference>
		<int value="5"/>
		<int value="12"/>
	</difference>
]]>
	</content>
</template>
</templates>
)",
R"(
<constraints>
<use>  <!-- template name not specified, line 3 relative constraint xml -->
	<with id="278"/>
</use>
</constraints>
)",
		"UseTagContainsTemplateAttr"
	},
	{
		TemplateSubstitutionErrorCode::RecursiveTemplateExpansion,
		7,
		// A use B, B use C, C use A
R"(
<templates>
<template name="A">
	<content>
<![CDATA[
	<use template="B"/>
]]>
	</content>
</template>
<template name="B">
	<content>
<![CDATA[
	<use template="C"/>
]]>
	</content>
</template>
<template name="C">
	<content>
<![CDATA[
	<!-- comment -->
	<difference>
		<int value="5"/>
		<int value="12"/>
	</difference>
	<use template="A"/>
]]>
	</content>
</template>
</templates>
)",
R"(
<constraints>
<use template="A"/>  <!-- recursive expansion, line 7 relative initial of C template body -->
</constraints>
)",
		"RecursiveTemplateExpansion"
	},
	{
		TemplateSubstitutionErrorCode::UseUndeclaredTemplate,
		6,
R"(
<templates>
<template name="C">
	<content>
<![CDATA[
	<difference>
		<int value="5"/>
		<int value="12"/>
	</difference>
	<use template="bober"/>
]]>
	</content>
</template>
</templates>
)",
R"(
<constraints>
<use template="C"/>  <!-- use indeclared template "bober", line 6 relative initial of C template body -->
</constraints>
)",
		"UseUndeclaredTemplate"
	},
};
// clazy:enable

INSTANTIATE_TEST_SUITE_P(
	AllErrors,
	XmlTemplateErrorTest,
	::testing::ValuesIn(testCases),
	[](const ::testing::TestParamInfo<ErrorTestCase>& info) {
		return info.param.testName;
	}
);

INSTANTIATE_TEST_SUITE_P(
	AllErrors,
	XmlTemplateParserErrorTest,
	::testing::ValuesIn(parserTestCases),
	[](const ::testing::TestParamInfo<ErrorTestCase>& info) {
		return info.param.testName;
	}
);

INSTANTIATE_TEST_SUITE_P(
	AllErrors,
	XmlTemplateSubstitutionErrorTest,
	::testing::ValuesIn(substitutionTestCases),
	[](const ::testing::TestParamInfo<SubstitutionErrorTestCase>& info) {
		return info.param.testName;
	}
);

INSTANTIATE_TEST_SUITE_P(
	AllErrors,
	XmlTemplateParserSubstitutionErrorTest,
	::testing::ValuesIn(substitutionParserTestCases),
	[](const ::testing::TestParamInfo<SubstitutionErrorTestCase>& info) {
		return info.param.testName;
	}
);
