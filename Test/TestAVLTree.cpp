#include <gtest/gtest.h>

#include "Tree/AVLTree.h"

class TestAVLSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestAVLSuite, ConstructorDefault)
{
    AVLTree<int> testObj;
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
}

TEST_F(TestAVLSuite, ConstructorInitializerList)
{
    AVLTree<int> testObj = {3, 1, 2, 5, 4};
    EXPECT_FALSE(testObj.empty());
    EXPECT_FALSE(testObj.get_root() == nullptr);
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_TRUE(testObj.is_valid());
}

TEST_F(TestAVLSuite, ConstructorAnotherTree)
{
    AVLTree<int> another = {5, 2, 6, 1, 8};
    AVLTree<int> testObj(another);
    EXPECT_FALSE(testObj.empty());
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_TRUE(testObj.is_valid());
}

TEST_F(TestAVLSuite, OperatorAssignmentList)
{
    AVLTree<int> testObj = {5, 2, 6, 1, 8};
    EXPECT_FALSE(testObj.empty());
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_TRUE(testObj.is_valid());
}

TEST_F(TestAVLSuite, OperatorAssignmentAnotherTree)
{
    AVLTree<int> another = {5, 2, 6, 1, 8};
    AVLTree<int> testObj = another;
    EXPECT_FALSE(testObj.empty());
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_TRUE(testObj.is_valid());
}

TEST_F(TestAVLSuite, OperatorCompareEqual)
{
    AVLTree<int> another;
    AVLTree<int> testObj;

    EXPECT_TRUE(testObj == another);

    another = {1, 2, 3, 4, 5};
    EXPECT_FALSE(testObj == another);

    testObj = {1, 2, 3, 4, 5};
    EXPECT_TRUE(testObj == another);

    testObj = {1, 1, 2, 2, 3, 3, 4, 4 , 5, 5};
    EXPECT_FALSE(testObj == another);

    another = testObj;
    EXPECT_TRUE(testObj == another);
}

TEST_F(TestAVLSuite, MethodIsSameSet)
{
    AVLTree<int> another;
    AVLTree<int> testObj;
    EXPECT_TRUE(testObj.is_same_set(another));

    another = {1, 2, 3, 4, 5};
    testObj = {3, 2, 1, 5, 4};
    EXPECT_TRUE(testObj.is_same_set(another));

    another.insert(1);
    testObj.insert(1);
    EXPECT_TRUE(testObj.is_same_set(another));

    another.insert(1);
    EXPECT_FALSE(testObj.is_same_set(another));
}

TEST_F(TestAVLSuite, MethodSwap)
{
    AVLTree<int> another = {1, 2, 3, 4, 5};
    AVLTree<int> testObj;

    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 0U);

    testObj.swap(another);
    EXPECT_FALSE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 5U);

    testObj.swap(another);
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 0U);
}

TEST_F(TestAVLSuite, MethodInsert)
{
    AVLTree<int> testObj;
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 0U);

    testObj.insert(5);
    EXPECT_FALSE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 1U);

    testObj.insert(5);
    EXPECT_FALSE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 2U);
    
    testObj.insert(1);
    EXPECT_FALSE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 3U);
    
    testObj.insert(9);
    EXPECT_FALSE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 4U);
}

TEST_F(TestAVLSuite, MethodContain)
{
    AVLTree<int> testObj;
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 0U);

    EXPECT_FALSE(testObj.contain(1));

    testObj.insert(5);
    EXPECT_FALSE(testObj.contain(1));

    testObj.insert(1);
    EXPECT_TRUE(testObj.contain(1));

    testObj.insert(7);
    EXPECT_TRUE(testObj.contain(7));

    EXPECT_FALSE(testObj.contain(3));
}

TEST_F(TestAVLSuite, MethodGetNode)
{
    AVLTree<int> testObj;
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 0U);

    const AVLTree<int>::Node* find_node = testObj.get_node(5);
    EXPECT_TRUE(find_node == nullptr);

    testObj.insert(5);
    find_node = testObj.get_node(5);
    EXPECT_EQ(find_node->data, 5);

    testObj.insert(7);
    find_node = testObj.get_node(7);
    EXPECT_EQ(find_node->data, 7);
}

TEST_F(TestAVLSuite, MethodErase)
{
    AVLTree<int> testObj;
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 0U);

    testObj.erase(5);
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 0U);

    testObj.insert(5);
    testObj.erase(5);
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 0U);

    testObj.insert(5);
    testObj.insert(3);
    testObj.insert(2);
    testObj.insert(7);
    testObj.insert(6);
    testObj.insert(9);
    testObj.insert(1);
    testObj.insert(8);
    testObj.insert(4);
    testObj.insert(0);

    for (int i = 0; i < 10; i++)
    {
        testObj.erase(i);
        EXPECT_TRUE(testObj.is_valid());
    }

    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestAVLSuite, MethodClear)
{
    AVLTree<int> testObj;
}

TEST_F(TestAVLSuite, MethodTraversal)
{
    AVLTree<int> testObj;
}

TEST_F(TestAVLSuite, MethodGetMinNode)
{
    AVLTree<int> testObj;
}

TEST_F(TestAVLSuite, MethodGetMaxNode)
{
    AVLTree<int> testObj;
}

TEST_F(TestAVLSuite, MethodGetLowestCommonAncestor)
{
    AVLTree<int> testObj;
}

TEST_F(TestAVLSuite, MethodHeight)
{
    AVLTree<int> testObj;
    EXPECT_EQ(testObj.height(), 0U);
}