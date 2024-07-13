#include <gtest/gtest.h>

#include "ContainerSequence/Deque.h"

class TestDequeSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestDequeSuite, ConstructorDefault)
{
    Deque<int> testObj;
}