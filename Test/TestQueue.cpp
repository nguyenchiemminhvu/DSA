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