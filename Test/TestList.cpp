#include <gtest/gtest.h>

#include "ContainerSequence/List.h"

class TestListSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestListSuite, ConstructorDefault)
{
    List<int> testObj;
}