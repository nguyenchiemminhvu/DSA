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

TEST_F(TestStackSuite, MethodSwap)
{
    Stack<int> testObj;
}

TEST_F(TestStackSuite, MethodPush)
{
    Stack<int> testObj;
}

TEST_F(TestStackSuite, MethodPop)
{
    Stack<int> testObj;
}

TEST_F(TestStackSuite, MethodTop)
{
    Stack<int> testObj;
}
