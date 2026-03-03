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

#include <gtest/gtest.h>
#include <src/engine/templates/details/template.h>
#include <src/engine/templates/details/templatesManager.h>

namespace qrTest {

class XmlTemplateMock;
class XmlTemplateParserMock;
class XmlTemplateProcessorMock;
namespace robotsTests {
namespace commonTwoDModelTests {

class XmlTemplateTestBase : public ::testing::Test
{
protected:
	void SetUp() override {};
	void TearDown() override {};
	~XmlTemplateTestBase() override = default;
};

using TemplateParseErrorCode = twoDModel::templates::details::XmlTemplate::TemplateParseErrorCode;
using TemplateSubstitutionErrorCode = twoDModel::templates::details::XmlTemplate::TemplateSubstitutionErrorCode;

struct ErrorTestCase {
	TemplateParseErrorCode expectedCode;
	int expectedLine;
	QString testXml;
	std::string testName;
};

class XmlTemplateErrorTest : public XmlTemplateTestBase,
			    public ::testing::WithParamInterface<ErrorTestCase> {
protected:
	void SetUp() override {
		XmlTemplateTestBase::SetUp();
		mCurrentTestCase = GetParam();
		mMockTemplate = std::make_unique<XmlTemplateMock>("test_template");
	}

	void TearDown() override {
		mMockTemplate.reset();
	}

	const ErrorTestCase& testCase() const { return mCurrentTestCase; }
	std::unique_ptr<XmlTemplateMock> mMockTemplate;

private:
	ErrorTestCase mCurrentTestCase;
};

class XmlTemplateParserErrorTest : public XmlTemplateTestBase,
			    public ::testing::WithParamInterface<ErrorTestCase> {
protected:
	void SetUp() override {
		XmlTemplateTestBase::SetUp();
		mCurrentTestCase = GetParam();
		mMockTemplateParser = std::make_unique<XmlTemplateParserMock>();
	}

	void TearDown() override {
		mMockTemplateParser.reset();
	}

	const ErrorTestCase& testCase() const { return mCurrentTestCase; }
	std::unique_ptr<XmlTemplateParserMock> mMockTemplateParser;
private:
	ErrorTestCase mCurrentTestCase;
};

struct SubstitutionErrorTestCase {
	TemplateSubstitutionErrorCode expectedCode;
	int expectedLine;
	QString templatesDefinition;
	QString testXml;
	std::string testName;
};

class XmlTemplateSubstitutionErrorTest : public XmlTemplateTestBase,
			    public ::testing::WithParamInterface<SubstitutionErrorTestCase> {
protected:
	void SetUp() override {
		XmlTemplateTestBase::SetUp();
		mMockTemplate = std::make_unique<XmlTemplateMock>("test_template");
	}

	void TearDown() override {
		mMockTemplate.reset();
	}

	const SubstitutionErrorTestCase& testCase() const { return mCurrentTestCase; }
	std::unique_ptr<XmlTemplateMock> mMockTemplate;
	//std::unique_ptr<XmlTemplateParserMock> mMockTemplateParser;
private:
	SubstitutionErrorTestCase mCurrentTestCase;
};

class XmlTemplateParserSubstitutionErrorTest : public XmlTemplateTestBase,
			    public ::testing::WithParamInterface<SubstitutionErrorTestCase> {
protected:
	void SetUp() override {
		XmlTemplateTestBase::SetUp();
		mTemplateManager = std::make_unique<twoDModel::templates::details::TemplatesManager>();
		mMockTemplateParser = std::make_unique<XmlTemplateParserMock>();
		mMockTemplateProcessor = std::make_unique<XmlTemplateProcessorMock>(mTemplateManager.get());
	}

	void TearDown() override {
		mMockTemplateProcessor.reset();
	}

	const SubstitutionErrorTestCase& testCase() const { return mCurrentTestCase; }
	std::unique_ptr<twoDModel::templates::details::TemplatesManager> mTemplateManager;
	std::unique_ptr<XmlTemplateParserMock> mMockTemplateParser;
	std::unique_ptr<XmlTemplateProcessorMock> mMockTemplateProcessor;
private:
	SubstitutionErrorTestCase mCurrentTestCase;
};

}
}
}
