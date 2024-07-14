#include <gtest/gtest.h>

#include "ContainerAdaptor/Stack.h"

class TestStackSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestStackSuite, ConstructorDefault)
{
    Stack<int> testObj;
}