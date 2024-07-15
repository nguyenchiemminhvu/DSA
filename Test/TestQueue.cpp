#include <gtest/gtest.h>

#include "ContainerAdaptor/Queue.h"

class TestQueueSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestQueueSuite, ConstructorDefault)
{
    Queue<int> testObj;
}

TEST_F(TestQueueSuite, MethodSwap)
{
    Queue<int> testObj;
}

TEST_F(TestQueueSuite, MethodPush)
{
    Queue<int> testObj;
}

TEST_F(TestQueueSuite, MethodPop)
{
    Queue<int> testObj;
}

TEST_F(TestQueueSuite, MethodFront)
{
    Queue<int> testObj;
}

TEST_F(TestQueueSuite, MethodBack)
{
    Queue<int> testObj;
}
