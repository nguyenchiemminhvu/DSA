#include <gtest/gtest.h>

#include "ContainerAssociative/Set.h"

class TestSetSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestSetSuite, ConstructorDefault)
{
    Set<int> testObj;
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestSetSuite, ConstructorInitializerList)
{
    Set<int> testObj = {4, 2, 6, 1, 2, 3, 5};
    EXPECT_EQ(testObj.size(), 7U);
}

TEST_F(TestSetSuite, ConstructorVector)
{
    std::vector<int> v = {4, 2, 6, 1, 2, 3, 5};
    Set<int> testObj(v);
    EXPECT_EQ(testObj.size(), 7U);
}

TEST_F(TestSetSuite, ConstructorAnotherSet)
{
    Set<int> another = {4, 2, 6, 1, 2, 3, 5};
    Set<int> testObj(another);
    EXPECT_EQ(testObj.size(), 7U);
}

TEST_F(TestSetSuite, MethodSwap)
{
    Set<int> another = {4, 2, 6, 1, 2, 3, 5};
    Set<int> testObj;
    EXPECT_TRUE(testObj.empty());

    testObj.swap(another);
    EXPECT_EQ(testObj.size(), 7U);

    testObj.swap(another);
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestSetSuite, MethodInsert)
{
    Set<int> testObj;
    EXPECT_TRUE(testObj.empty());

    testObj.insert(3);
    EXPECT_EQ(testObj.size(), 1U);

    testObj.insert(3);
    EXPECT_EQ(testObj.size(), 2U);

    testObj.insert(5);
    EXPECT_EQ(testObj.size(), 3U);
}

TEST_F(TestSetSuite, MethodErase)
{
    Set<int> testObj;
    EXPECT_TRUE(testObj.empty());

    testObj.erase(3);
    EXPECT_TRUE(testObj.empty());

    testObj.insert(5);
    testObj.insert(2);
    testObj.insert(7);
    EXPECT_EQ(testObj.size(), 3U);

    testObj.erase(2);
    EXPECT_EQ(testObj.size(), 2U);

    testObj.erase(5);
    EXPECT_EQ(testObj.size(), 1U);

    testObj.erase(7);
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestSetSuite, MethodClear)
{
    Set<int> testObj;
    EXPECT_TRUE(testObj.empty());

    testObj.clear();
    EXPECT_TRUE(testObj.empty());

    testObj.insert(4);
    testObj.insert(7);
    testObj.insert(1);
    testObj.insert(5);
    testObj.clear();
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestSetSuite, MethodContain)
{
    Set<int> testObj;
    EXPECT_FALSE(testObj.contain(5));

    testObj.insert(5);
    EXPECT_TRUE(testObj.contain(5));

    testObj.insert(2);
    EXPECT_TRUE(testObj.contain(2));

    testObj.insert(2);
    EXPECT_TRUE(testObj.contain(2));

    testObj.insert(6);
    EXPECT_TRUE(testObj.contain(6));

    testObj.insert(7);
    EXPECT_TRUE(testObj.contain(7));

    EXPECT_FALSE(testObj.contain(10));
}

TEST_F(TestSetSuite, MethodCount)
{
    Set<int> testObj;
    EXPECT_EQ(testObj.count(5), 0U);

    testObj.insert(5);
    EXPECT_EQ(testObj.count(5), 1U);

    testObj.insert(5);
    EXPECT_EQ(testObj.count(5), 2U);

    testObj.insert(5);
    EXPECT_EQ(testObj.count(5), 3U);

    testObj.insert(1);
    EXPECT_EQ(testObj.count(1), 1U);

    testObj.insert(2);
    EXPECT_EQ(testObj.count(2), 1U);

    EXPECT_EQ(testObj.count(10), 0U);
}
