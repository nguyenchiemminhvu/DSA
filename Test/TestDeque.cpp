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
    EXPECT_THROW(testObj.front(), std::out_of_range);
    EXPECT_THROW(testObj.back(), std::out_of_range);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);
}

TEST_F(TestDequeSuite, ConstructorInitializerList)
{
    Deque<int> testObj = {1, 2, 3, 4, 5};
    EXPECT_NO_THROW(testObj.front());
    EXPECT_NO_THROW(testObj.back());
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_EQ(testObj.capacity(), 5U);
    EXPECT_EQ(testObj.front(), 1);
    EXPECT_EQ(testObj.back(), 5);
}

TEST_F(TestDequeSuite, ConstructorAnotherDeque)
{
    Deque<int> another = {1, 2, 3, 4, 5};
    Deque<int> testObj(another);
    EXPECT_NO_THROW(testObj.front());
    EXPECT_NO_THROW(testObj.back());
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_EQ(testObj.capacity(), 5U);
    EXPECT_EQ(testObj.front(), 1);
    EXPECT_EQ(testObj.back(), 5);
}

TEST_F(TestDequeSuite, MethodSwap)
{
    Deque<int> another = {1, 2, 3, 4, 5};
    Deque<int> testObj;
    EXPECT_THROW(testObj.front(), std::out_of_range);
    EXPECT_THROW(testObj.back(), std::out_of_range);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);

    testObj.swap(another);
    EXPECT_NO_THROW(testObj.front());
    EXPECT_NO_THROW(testObj.back());
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_EQ(testObj.capacity(), 5U);
    EXPECT_EQ(testObj.front(), 1);
    EXPECT_EQ(testObj.back(), 5);

    testObj.swap(another);
    EXPECT_THROW(testObj.front(), std::out_of_range);
    EXPECT_THROW(testObj.back(), std::out_of_range);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);
}

TEST_F(TestDequeSuite, OperatorAccessElement)
{
    Deque<int> testObj;
    EXPECT_THROW(testObj[0U], std::out_of_range);

    testObj.push_back(1);
    EXPECT_NO_THROW(testObj[0U]);
    EXPECT_EQ(testObj[0U], 1);
    
    testObj.push_front(2);
    EXPECT_NO_THROW(testObj[0U]);
    EXPECT_EQ(testObj[0U], 2);

    testObj.push_back(3);
    EXPECT_EQ(testObj[0U], 2);
    EXPECT_EQ(testObj[1U], 1);
    EXPECT_EQ(testObj[2U], 3);
}

TEST_F(TestDequeSuite, MethodPushBack)
{
    Deque<int> testObj;
    EXPECT_THROW(testObj[0U], std::out_of_range);

    for (int i = 0; i < 5; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.push_back(i));
    }

    for (std::size_t i = 0U; i < 5U; i++)
    {
        EXPECT_EQ(testObj[i], static_cast<int>(i));
    }
}

TEST_F(TestDequeSuite, MethodPushFront)
{
    Deque<int> testObj;
    EXPECT_THROW(testObj[0U], std::out_of_range);

    for (int i = 0; i < 5; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.push_front(i));
    }

    for (std::size_t i = 0U; i < 5U; i++)
    {
        EXPECT_EQ(testObj[i], static_cast<int>(4 - i));
    }
}

TEST_F(TestDequeSuite, MethodPopBack)
{
    Deque<int> testObj;
    EXPECT_THROW(testObj.pop_back(), std::out_of_range);

    testObj.push_back(1);
    EXPECT_NO_THROW(testObj.pop_back());
    EXPECT_THROW(testObj.pop_back(), std::out_of_range);

    for (int i = 0; i < 5; i++)
    {
        testObj.push_back(i);
    }

    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(testObj.back(), 4 - i);
        testObj.pop_back();
    }

    EXPECT_THROW(testObj.pop_back(), std::out_of_range);
}

TEST_F(TestDequeSuite, MethodPopFront)
{
    Deque<int> testObj;
    EXPECT_THROW(testObj.pop_front(), std::out_of_range);

    testObj.push_front(1);
    EXPECT_NO_THROW(testObj.pop_front());
    EXPECT_THROW(testObj.pop_front(), std::out_of_range);

    for (int i = 0; i < 5; i++)
    {
        testObj.push_front(i);
    }

    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(testObj.front(), 4 - i);
        testObj.pop_front();
    }

    EXPECT_THROW(testObj.pop_front(), std::out_of_range);
}

TEST_F(TestDequeSuite, MethodClear)
{
    Deque<int> testObj;
    EXPECT_THROW(testObj.back(), std::out_of_range);

    EXPECT_NO_FATAL_FAILURE(testObj.clear());
    EXPECT_THROW(testObj.back(), std::out_of_range);

    for (int i = 0; i < 5; i++)
    {
        testObj.push_back(i);
    }

    EXPECT_NO_THROW(testObj.back());
    testObj.clear();
    EXPECT_THROW(testObj.back(), std::out_of_range);
}
