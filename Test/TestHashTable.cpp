#include <gtest/gtest.h>

#include "HashTable/HashTable.h"

class TestHashSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestHashSuite, ConstructorDefault)
{
    HashTable<int, int> testObj;
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestHashSuite, MethodSwap)
{
    HashTable<int, int> another;
    another.insert(1, 0);
    another.insert(2, 0);
    another.insert(3, 0);

    HashTable<int, int> testObj;
    EXPECT_EQ(testObj.size(), 0U);

    testObj.swap(another);
    EXPECT_EQ(testObj.size(), 3U);

    testObj.swap(another);
    EXPECT_EQ(testObj.size(), 0U);
}

TEST_F(TestHashSuite, MethodInsert)
{
    HashTable<int, int> testObj;
    for (int i = 0; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.insert(i, 0));
    }

    EXPECT_EQ(testObj.size(), 100U);
}

TEST_F(TestHashSuite, MethodRetrieve)
{
    HashTable<int, int> testObj;
    for (int i = 0; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.insert(i, 10));
    }

    for (int i = 0; i < 100; i++)
    {
        EXPECT_EQ(testObj.retrieve(i), 10);
    }

    EXPECT_THROW(testObj.retrieve(100), std::out_of_range);
}

TEST_F(TestHashSuite, MethodContain)
{
    HashTable<int, int> testObj;
    for (int i = 0; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.insert(i, 10));
    }

    for (int i = 0; i < 100; i++)
    {
        EXPECT_TRUE(testObj.contain(i));
    }

    EXPECT_FALSE(testObj.contain(100));
}

TEST_F(TestHashSuite, MethodRemove)
{
    HashTable<int, int> testObj;
    for (int i = 0; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.insert(i, 10));
    }
    EXPECT_EQ(testObj.size(), 100U);

    for (int i = 50; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.remove(i));
    }
    EXPECT_EQ(testObj.size(), 50U);

    for (int i = 0; i < 50; i++)
    {
        EXPECT_TRUE(testObj.contain(i));
    }

    for (int i = 50; i < 100; i++)
    {
        EXPECT_FALSE(testObj.contain(i));
    }

    EXPECT_THROW(testObj.remove(100), std::out_of_range);
}

TEST_F(TestHashSuite, MethodClear)
{
    HashTable<int, int> testObj;
    for (int i = 0; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.insert(i, 10));
    }
    EXPECT_EQ(testObj.size(), 100U);

    testObj.clear();

    EXPECT_EQ(testObj.size(), 0U);
}
