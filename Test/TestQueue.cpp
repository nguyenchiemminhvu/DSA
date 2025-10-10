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
    EXPECT_TRUE(testObj.empty());
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_THROW(testObj.front(), std::out_of_range);
}

TEST_F(TestQueueSuite, MethodSwap)
{
    Queue<int> testObj;
    EXPECT_TRUE(testObj.empty());
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_THROW(testObj.front(), std::out_of_range);

    Queue<int> another;
    another.push(1);
    another.push(2);
    another.push(3);

    testObj.swap(another);
    EXPECT_FALSE(testObj.empty());
    EXPECT_EQ(testObj.size(), 3U);
    
    testObj.swap(another);
    EXPECT_TRUE(testObj.empty());
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_THROW(testObj.front(), std::out_of_range);
}

TEST_F(TestQueueSuite, MethodPush)
{
    Queue<int> testObj;
    EXPECT_TRUE(testObj.empty());
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_THROW(testObj.front(), std::out_of_range);

    testObj.push(1);
    EXPECT_EQ(testObj.front(), 1);

    testObj.push(2);
    EXPECT_EQ(testObj.front(), 1);
}

TEST_F(TestQueueSuite, MethodPop)
{
    Queue<int> testObj;
    EXPECT_TRUE(testObj.empty());
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_THROW(testObj.front(), std::out_of_range);

    testObj.push(1);
    testObj.push(2);

    testObj.pop();
    EXPECT_EQ(testObj.front(), 2);

    testObj.pop();
    EXPECT_THROW(testObj.front(), std::out_of_range);

    EXPECT_THROW(testObj.pop(), std::out_of_range);
}

TEST_F(TestQueueSuite, MethodFront)
{
    Queue<int> testObj;
    EXPECT_TRUE(testObj.empty());
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_THROW(testObj.front(), std::out_of_range);

    testObj.push(1);
    EXPECT_EQ(testObj.front(), 1);

    testObj.push(2);
    EXPECT_EQ(testObj.front(), 1);

    testObj.pop();
    EXPECT_EQ(testObj.front(), 2);
}
