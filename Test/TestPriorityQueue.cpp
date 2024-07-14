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