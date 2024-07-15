#include <gtest/gtest.h>

#include "ContainerAdaptor/PriorityQueue.h"

class TestPriorityQueueSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestPriorityQueueSuite, ConstructorDefault)
{
    PriorityQueue<int> testObj;
}

TEST_F(TestPriorityQueueSuite, ConstructorInitializerList)
{
    PriorityQueue<int> testObj;
}

TEST_F(TestPriorityQueueSuite, ConstructorAnotherPriorityQueue)
{
    PriorityQueue<int> testObj;
}

TEST_F(TestPriorityQueueSuite, MethodSwap)
{
    PriorityQueue<int> testObj;
}

TEST_F(TestPriorityQueueSuite, MethodPush)
{
    PriorityQueue<int> testObj;
}

TEST_F(TestPriorityQueueSuite, MethodPop)
{
    PriorityQueue<int> testObj;
}

TEST_F(TestPriorityQueueSuite, MethodTop)
{
    PriorityQueue<int> testObj;
}
