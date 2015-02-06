#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <src/engine/constraints/details/constraintsParser.h>
#include <src/engine/model/timeline.h>

namespace qrTest {
namespace robotsTests {
namespace commonTwoDModelTests {

/// Tests for ConstraintsParser.
class ConstraintsParserTests : public testing::Test
{
public:
	ConstraintsParserTests();

protected:
	void SetUp() override;
	void clearEverything();

	twoDModel::constraints::details::Events mEvents;
	twoDModel::constraints::details::Variables mVariables;
	twoDModel::constraints::details::Objects mObjects;
	twoDModel::model::Timeline mTimeline;
	twoDModel::constraints::details::ConstraintsParser mParser;
};

}
}
}
