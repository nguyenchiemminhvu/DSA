#include <gtest/gtest.h>

#include "ContainerUnorderedAssociative/UnorderedMap.h"

class TestUnorderedMapSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestUnorderedMapSuite, ConstructorDefault)
{
    UnorderedMap<int, int> testObj;
    EXPECT_TRUE(testObj.empty());
}
