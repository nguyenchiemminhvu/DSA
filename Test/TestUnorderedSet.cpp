#include <gtest/gtest.h>

#include "ContainerUnorderedAssociative/UnorderedSet.h"

class TestUnorderedSetSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestUnorderedSetSuite, ConstructorDefault)
{
    UnorderedSet<int> testObj;
}

