#include <gtest/gtest.h>

#include "ContainerAssociative/Map.h"

class TestMapSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestMapSuite, ConstructorDefault)
{
    Map<int, int> testObj;
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestMapSuite, ConstructorAnotherMap)
{
    Map<int, int> another;
    Map<int, int> testObj(another);
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestMapSuite, OpeatorAssignmentAnotherMap)
{
    Map<int, int> another;
    Map<int, int> testObj = another;
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestMapSuite, MethodSwap)
{
    Map<int, int> another;
    Map<int, int> testObj;
    testObj.swap(another);
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestMapSuite, MethodInsert)
{
    Map<int, int> testObj;
    for (int i = 0; i < 10; i++)
    {
        testObj.insert(i, 1);
    }

    for (int i = 0; i < 10; i++)
    {
        EXPECT_NO_THROW(testObj.at(i));
    }
}

TEST_F(TestMapSuite, MethodContain)
{
    Map<int, int> testObj;
    for (int i = 0; i < 10; i++)
    {
        testObj.insert(i, 1);
    }

    for (int i = 0; i < 10; i++)
    {
        EXPECT_TRUE(testObj.contain(i));
    }

    EXPECT_FALSE(testObj.contain(10));
}

TEST_F(TestMapSuite, MethodErase)
{
    Map<int, int> testObj;
    for (int i = 0; i < 10; i++)
    {
        testObj.insert(i, 1);
    }

    EXPECT_EQ(testObj.size(), 10U);

    for (int i = 0; i < 10; i++)
    {
        testObj.erase(i);
    }

    for (int i = 0; i < 10; i++)
    {
        EXPECT_FALSE(testObj.contain(i));
    }

    EXPECT_EQ(testObj.size(), 0U);
}

TEST_F(TestMapSuite, MethodClear)
{
    Map<int, int> testObj;
    for (int i = 0; i < 10; i++)
    {
        testObj.insert(i, 1);
    }

    EXPECT_EQ(testObj.size(), 10U);

    testObj.clear();

    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestMapSuite, MethodAt)
{
    Map<int, int> testObj;
    EXPECT_THROW(testObj.at(5), std::out_of_range);

    for (int i = 0; i < 10; i++)
    {
        testObj.insert(i, 1);
    }

    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ(testObj.at(i), 1);
    }
}

TEST_F(TestMapSuite, OperatorAccessByKey)
{
    Map<int, int> testObj;
    for (int i = 0; i < 10; i++)
    {
        testObj[i] = 1;
    }

    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ(testObj[i], 1);
    }
}
