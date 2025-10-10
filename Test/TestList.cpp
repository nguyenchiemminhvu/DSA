#include <gtest/gtest.h>

#include "ContainerSequence/List.h"

class TestListSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestListSuite, ConstructorDefault)
{
    List<int> testObj;
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestListSuite, ConstructorInitializerList)
{
    List<int> testObj = {1, 2, 3, 4, 5};
    EXPECT_FALSE(testObj.empty());

    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_EQ(testObj.front(), 1);
    EXPECT_EQ(testObj.back(), 5);
}

TEST_F(TestListSuite, ConstructorAnotherList)
{
    List<int> another = {1, 2, 3, 4, 5};
    List<int> testObj(another);
    EXPECT_FALSE(testObj.empty());

    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_EQ(testObj.front(), 1);
    EXPECT_EQ(testObj.back(), 5);
}

TEST_F(TestListSuite, MethodSwap)
{
    List<int> another = {1, 2, 3, 4, 5};
    List<int> testObj;
    EXPECT_TRUE(testObj.empty());

    testObj.swap(another);
    EXPECT_FALSE(testObj.empty());
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_EQ(testObj.front(), 1);
    EXPECT_EQ(testObj.back(), 5);

    testObj.swap(another);
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestListSuite, MethodPushBack)
{
    List<int> testObj;
    EXPECT_THROW(testObj.back(), std::out_of_range);

    testObj.push_back(1);
    EXPECT_EQ(testObj.back(), 1);

    testObj.push_back(2);
    EXPECT_EQ(testObj.back(), 2);

    testObj.push_back(3);
    EXPECT_EQ(testObj.back(), 3);
}

TEST_F(TestListSuite, MethodPushFront)
{
    List<int> testObj;
    EXPECT_THROW(testObj.front(), std::out_of_range);

    testObj.push_front(1);
    EXPECT_EQ(testObj.front(), 1);

    testObj.push_front(2);
    EXPECT_EQ(testObj.front(), 2);

    testObj.push_front(3);
    EXPECT_EQ(testObj.front(), 3);
}

TEST_F(TestListSuite, MethodPopBack)
{
    List<int> testObj;
    EXPECT_NO_FATAL_FAILURE(testObj.pop_back());

    testObj.push_back(1);
    EXPECT_EQ(testObj.back(), 1);
    testObj.pop_back();
    EXPECT_THROW(testObj.back(), std::out_of_range);

    testObj.push_back(1);
    testObj.push_back(2);
    testObj.pop_back();
    EXPECT_EQ(testObj.back(), 1);
}

TEST_F(TestListSuite, MethodPopFront)
{
    List<int> testObj;
    EXPECT_NO_FATAL_FAILURE(testObj.pop_front());

    testObj.push_front(1);
    EXPECT_EQ(testObj.front(), 1);
    testObj.pop_front();
    EXPECT_THROW(testObj.front(), std::out_of_range);

    testObj.push_front(1);
    testObj.push_front(2);
    testObj.pop_front();
    EXPECT_EQ(testObj.front(), 1);
}

TEST_F(TestListSuite, MethodClear)
{
    List<int> testObj;
    EXPECT_NO_FATAL_FAILURE(testObj.clear());

    testObj.push_back(1);
    testObj.push_back(2);
    testObj.push_back(3);
    EXPECT_NO_THROW(testObj.back());
    EXPECT_NO_FATAL_FAILURE(testObj.clear());

    EXPECT_THROW(testObj.back(), std::out_of_range);
}

TEST_F(TestListSuite, MethodAccessFront)
{
    List<int> testObj;
    EXPECT_THROW(testObj.front(), std::out_of_range);

    testObj.push_back(1);
    EXPECT_EQ(testObj.front(), 1);

    testObj.push_back(2);
    EXPECT_EQ(testObj.front(), 1);

    testObj.push_front(0);
    EXPECT_EQ(testObj.front(), 0);    
}

TEST_F(TestListSuite, MethodAccessBack)
{
    List<int> testObj;
    EXPECT_THROW(testObj.back(), std::out_of_range);

    testObj.push_back(1);
    EXPECT_EQ(testObj.back(), 1);

    testObj.push_front(2);
    EXPECT_EQ(testObj.back(), 1);

    testObj.push_back(0);
    EXPECT_EQ(testObj.back(), 0);
}

TEST_F(TestListSuite, MethodGetSize)
{
    List<int> testObj;
    EXPECT_EQ(testObj.size(), 0U);

    testObj.push_back(1);
    EXPECT_EQ(testObj.size(), 1U);

    testObj.push_front(1);
    EXPECT_EQ(testObj.size(), 2U);

    testObj.clear();
    EXPECT_EQ(testObj.size(), 0U);
}

TEST_F(TestListSuite, MethodEmpty)
{
    List<int> testObj;
    EXPECT_TRUE(testObj.empty());

    testObj.push_back(1);
    EXPECT_FALSE(testObj.empty());

    testObj.pop_back();
    EXPECT_TRUE(testObj.empty());

    testObj.push_back(1);
    testObj.clear();
    EXPECT_TRUE(testObj.empty());
}
