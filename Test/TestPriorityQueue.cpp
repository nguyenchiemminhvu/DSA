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
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestPriorityQueueSuite, ConstructorInitializerList)
{
    PriorityQueue<int> min_heap = {2, 3, 1, 5, 4};
    EXPECT_FALSE(min_heap.empty());
    EXPECT_EQ(min_heap.size(), 5U);
    EXPECT_EQ(min_heap.top(), 1);

    PriorityQueue<int, std::greater<int>> max_heap = {2, 3, 1, 5, 4};
    EXPECT_FALSE(max_heap.empty());
    EXPECT_EQ(max_heap.size(), 5U);
    EXPECT_EQ(max_heap.top(), 5);
}

TEST_F(TestPriorityQueueSuite, ConstructorAnotherPriorityQueue)
{
    PriorityQueue<int> min_heap = {2, 3, 1, 5, 4};
    PriorityQueue<int, std::greater<int>> max_heap = {2, 3, 1, 5, 4};

    PriorityQueue<int> testObj1(min_heap);
    EXPECT_FALSE(testObj1.empty());
    EXPECT_EQ(testObj1.size(), 5U);
    EXPECT_EQ(testObj1.top(), 1);

    PriorityQueue<int, std::greater<int>> testObj2(max_heap);
    EXPECT_FALSE(testObj2.empty());
    EXPECT_EQ(testObj2.size(), 5U);
    EXPECT_EQ(testObj2.top(), 5);
}

TEST_F(TestPriorityQueueSuite, MethodSwap)
{
    PriorityQueue<int> testObj;
    EXPECT_TRUE(testObj.empty());

    PriorityQueue<int> another = {2, 3, 1, 5, 4};
    testObj.swap(another);
    EXPECT_FALSE(testObj.empty());
    EXPECT_EQ(testObj.top(), 1);

    testObj.swap(another);
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestPriorityQueueSuite, MethodPush)
{
    PriorityQueue<int> testObj;
    EXPECT_TRUE(testObj.empty());

    testObj.push(1);
    EXPECT_FALSE(testObj.empty());
    EXPECT_EQ(testObj.top(), 1);

    testObj.push(2);
    EXPECT_FALSE(testObj.empty());
    EXPECT_EQ(testObj.top(), 1);

    testObj.push(0);
    EXPECT_FALSE(testObj.empty());
    EXPECT_EQ(testObj.top(), 0);
}

TEST_F(TestPriorityQueueSuite, MethodPop)
{
    PriorityQueue<int> testObj;
    EXPECT_THROW(testObj.pop(), std::out_of_range);

    testObj.push(1);
    EXPECT_NO_THROW(testObj.pop());

    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestPriorityQueueSuite, MethodTop)
{
    PriorityQueue<int> testObj;
    EXPECT_THROW(testObj.top(), std::out_of_range);

    testObj.push(1);
    EXPECT_EQ(testObj.top(), 1);

    testObj.push(0);
    EXPECT_EQ(testObj.top(), 0);

    testObj.push(-1);
    EXPECT_EQ(testObj.top(), -1);
}
