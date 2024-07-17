#include <gtest/gtest.h>

#include "Tree/BinarySearchTree.h"

class TestBSTSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestBSTSuite, ConstructorDefault)
{
    BinarySearchTree<int> testObj;
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.get_root() == nullptr);
    EXPECT_TRUE(testObj.is_valid());
}

TEST_F(TestBSTSuite, ConstructorInitializerList)
{
    BinarySearchTree<int> testObj = {3, 1, 2, 5, 4};
    EXPECT_FALSE(testObj.empty());
    EXPECT_FALSE(testObj.get_root() == nullptr);
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_TRUE(testObj.is_valid());
}

TEST_F(TestBSTSuite, ConstructorAnotherTree)
{
    BinarySearchTree<int> another = {3, 1, 2, 5, 4};
    BinarySearchTree<int> testObj(another);
    EXPECT_FALSE(testObj.empty());
    EXPECT_FALSE(testObj.get_root() == nullptr);
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_TRUE(testObj.is_valid());
}

TEST_F(TestBSTSuite, OperatorCompareEqual)
{
    BinarySearchTree<int> testObj;
    BinarySearchTree<int> another;
    EXPECT_TRUE(testObj == another);

    testObj.insert(1);
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_FALSE(testObj == another);

    another.insert(1);
    EXPECT_TRUE(testObj == another);

    testObj.insert(1);
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_FALSE(testObj == another);

    another.insert(1);
    EXPECT_TRUE(testObj == another);

    testObj.insert(2);
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_FALSE(testObj == another);

    another.insert(2);
    EXPECT_TRUE(testObj == another);
}

TEST_F(TestBSTSuite, MethodSwap)
{
    BinarySearchTree<int> testObj;
}

TEST_F(TestBSTSuite, MethodGetNode)
{
    BinarySearchTree<int> testObj;
}

TEST_F(TestBSTSuite, MethodInsert)
{
    BinarySearchTree<int> testObj;
}

TEST_F(TestBSTSuite, MethodContain)
{
    BinarySearchTree<int> testObj;
}

TEST_F(TestBSTSuite, MethodErase)
{
    BinarySearchTree<int> testObj;
}

TEST_F(TestBSTSuite, MethodClear)
{
    BinarySearchTree<int> testObj;
}

TEST_F(TestBSTSuite, MethodTraversal)
{
    BinarySearchTree<int> testObj;
}