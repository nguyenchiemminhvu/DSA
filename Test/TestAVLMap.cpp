#include <gtest/gtest.h>

#include "Tree/AVLTree.h"

class TestAVLMapSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestAVLMapSuite, ConstructorDefault)
{
    AVLMap<int, int> testObj;
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
}

TEST_F(TestAVLMapSuite, ConstructorAnother)
{
    AVLMap<int, int> another;
    AVLMap<int, int> testObj(another);
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), another.size());
}

TEST_F(TestAVLMapSuite, OperatorAssignmentAnother)
{
    AVLMap<int, int> another;
    AVLMap<int, int> testObj;
    testObj = another;
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), another.size());
}

TEST_F(TestAVLMapSuite, OperatorCompareEqual)
{
    AVLMap<int, int> another;
    AVLMap<int, int> testObj;
    EXPECT_TRUE(testObj == another);
}

TEST_F(TestAVLMapSuite, MethodSwap)
{
    AVLMap<int, int> another;
    AVLMap<int, int> testObj;
    EXPECT_NO_FATAL_FAILURE(testObj.swap(another));
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_NO_FATAL_FAILURE(testObj.swap(another));
}

TEST_F(TestAVLMapSuite, MethodInsert)
{
    AVLMap<int, int> testObj;
    EXPECT_NO_FATAL_FAILURE(testObj.insert(5, 1));
    EXPECT_NO_FATAL_FAILURE(testObj.insert(5, 2));
    EXPECT_NO_FATAL_FAILURE(testObj.insert(2, 3));
}

TEST_F(TestAVLMapSuite, MethodContain)
{
    AVLMap<int, int> testObj;
    // EXPECT_FALSE(testObj.contain(5));

    testObj.insert(5, 2);
    testObj.insert(1, 1);
    testObj.insert(2, 2);
    testObj.insert(3, 3);

    // EXPECT_TRUE(testObj.contain(5));
    // EXPECT_TRUE(testObj.contain(1));
    // EXPECT_TRUE(testObj.contain(2));
    // EXPECT_TRUE(testObj.contain(3));
    // EXPECT_FALSE(testObj.contain(4));
}

TEST_F(TestAVLMapSuite, MethodGetNode)
{
    AVLMap<int, int> testObj;
    EXPECT_TRUE(testObj.get_node(5) == nullptr);

    for (int i = 0; i < 10; i++)
    {
        testObj.insert(i, 1);
    }

    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.get_node(0)->value, 1);
    EXPECT_EQ(testObj.get_node(5)->value, 1);
    EXPECT_TRUE(testObj.get_node(10) == nullptr);
}

TEST_F(TestAVLMapSuite, MethodErase)
{
    AVLMap<int, int> testObj;
    EXPECT_NO_FATAL_FAILURE(testObj.erase(5));

    for (int i = 0; i < 10; i++)
    {
        testObj.insert(i, 1);
    }

    EXPECT_TRUE(testObj.is_valid());

    for (int i = 0; i < 10; i++)
    {
        testObj.erase(i);
        EXPECT_TRUE(testObj.is_valid());
    }

    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestAVLMapSuite, MethodClear)
{
    AVLMap<int, int> testObj;
}
