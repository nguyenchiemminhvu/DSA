#include <gtest/gtest.h>

#include "ContainerUnorderedAssociative/UnorderedMap.h"

class TestUnorderedMapSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestUnorderedMapSuite, ConstructorDefault)
{
    UnorderedMap<int, int> testObj;
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestUnorderedMapSuite, MethodSwap)
{
    UnorderedMap<int, int> testObj;
    EXPECT_TRUE(testObj.empty());

    UnorderedMap<int, int> another;
    another.insert(1, 1);

    testObj.swap(another);
    EXPECT_EQ(testObj.size(), 1U);

    testObj.swap(another);
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestUnorderedMapSuite, MethodInsert)
{
    UnorderedMap<int, int> testObj;
    EXPECT_TRUE(testObj.empty());

    for (int i = 0; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.insert(i, 100));
    }

    EXPECT_EQ(testObj.size(), 100U);
}

TEST_F(TestUnorderedMapSuite, MethodContain)
{
    UnorderedMap<int, int> testObj;
    EXPECT_TRUE(testObj.empty());

    for (int i = 0; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.insert(i, 100));
    }

    for (int i = 0; i < 100; i++)
    {
        EXPECT_TRUE(testObj.contain(i));
    }

    EXPECT_FALSE(testObj.contain(100));
}

TEST_F(TestUnorderedMapSuite, MethodAt)
{
    UnorderedMap<int, int> testObj;
    EXPECT_TRUE(testObj.empty());

    for (int i = 0; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.insert(i, 100));
    }

    for (int i = 0; i < 100; i++)
    {
        EXPECT_EQ(testObj.at(i), 100);
    }

    testObj.insert(10, 10);
    EXPECT_EQ(testObj.at(10), 100);

    EXPECT_THROW(testObj.at(100), std::out_of_range);
}

TEST_F(TestUnorderedMapSuite, OperatorAccessViaKey)
{
    UnorderedMap<int, int> testObj;
    EXPECT_TRUE(testObj.empty());

    for (int i = 0; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.insert(i, 100));
    }

    for (int i = 0; i < 100; i++)
    {
        EXPECT_EQ(testObj[i], 100);
    }

    for (int i = 0; i < 100; i++)
    {
        testObj[i] = 10;
    }

    for (int i = 0; i < 100; i++)
    {
        EXPECT_EQ(testObj[i], 10);
    }

    testObj[100] = 10;
    EXPECT_EQ(testObj[100], 10);
}

TEST_F(TestUnorderedMapSuite, MethodErase)
{
    UnorderedMap<int, int> testObj;
    EXPECT_TRUE(testObj.empty());

    for (int i = 0; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.insert(i, 100));
    }

    for (int i = 50; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.erase(i));
    }

    for (int i = 0; i < 50; i++)
    {
        EXPECT_TRUE(testObj.contain(i));
    }

    for (int i = 50; i < 100; i++)
    {
        EXPECT_FALSE(testObj.contain(i));
    }
}

TEST_F(TestUnorderedMapSuite, MethodClear)
{
    UnorderedMap<int, int> testObj;
    EXPECT_TRUE(testObj.empty());

    for (int i = 0; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.insert(i, 100));
    }
    EXPECT_EQ(testObj.size(), 100U);

    testObj.clear();

    EXPECT_EQ(testObj.size(), 0U);
}