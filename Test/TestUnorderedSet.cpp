#include <gtest/gtest.h>

#include "ContainerUnorderedAssociative/UnorderedSet.h"

class TestUnorderedSetSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestUnorderedSetSuite, ConstructorDefault)
{
    UnorderedSet<int> testObj;
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestUnorderedSetSuite, ConstructorInitializerList)
{
    UnorderedSet<int> testObj = {1, 2, 3, 4, 5};
    EXPECT_EQ(testObj.size(), 5U);
}

TEST_F(TestUnorderedSetSuite, ConstructorVector)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    UnorderedSet<int> testObj(v);
    EXPECT_EQ(testObj.size(), 5U);
}

TEST_F(TestUnorderedSetSuite, MethodSwap)
{
    UnorderedSet<int> testObj;
    EXPECT_TRUE(testObj.empty());

    UnorderedSet<int> another = {1, 2, 3, 4, 5};
    testObj.swap(another);
    EXPECT_EQ(testObj.size(), 5U);

    testObj.swap(another);
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestUnorderedSetSuite, MethodInsert)
{
    UnorderedSet<int> testObj;
    EXPECT_TRUE(testObj.empty());

    for (int i = 0; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.insert(i));
    }
    EXPECT_EQ(testObj.size(), 100U);
}

TEST_F(TestUnorderedSetSuite, MethodContain)
{
    UnorderedSet<int> testObj;
    EXPECT_TRUE(testObj.empty());

    for (int i = 0; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.insert(i));
    }

    for (int i = 0; i < 100; i++)
    {
        EXPECT_TRUE(testObj.contain(i));
    }

    EXPECT_FALSE(testObj.contain(100));
}

TEST_F(TestUnorderedSetSuite, MethodErase)
{
    UnorderedSet<int> testObj;
    EXPECT_TRUE(testObj.empty());

    for (int i = 0; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.insert(i));
    }

    for (int i = 0; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.erase(i));
    }

    EXPECT_THROW(testObj.erase(100), std::out_of_range);
}

TEST_F(TestUnorderedSetSuite, MethodClear)
{
    UnorderedSet<int> testObj;
    EXPECT_TRUE(testObj.empty());

    for (int i = 0; i < 100; i++)
    {
        EXPECT_NO_FATAL_FAILURE(testObj.insert(i));
    }

    testObj.clear();
    EXPECT_TRUE(testObj.empty());
}
