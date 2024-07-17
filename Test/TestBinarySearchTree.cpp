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

TEST_F(TestBSTSuite, OperatorAssignmentList)
{
    BinarySearchTree<int> testObj;
    testObj = {3, 1, 2, 5, 4};
    EXPECT_FALSE(testObj.empty());
    EXPECT_FALSE(testObj.get_root() == nullptr);
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_TRUE(testObj.is_valid());

    testObj = {3, 1, 2, 5, 4, 7, 6};
    EXPECT_FALSE(testObj.empty());
    EXPECT_FALSE(testObj.get_root() == nullptr);
    EXPECT_EQ(testObj.size(), 7U);
    EXPECT_TRUE(testObj.is_valid());
}

TEST_F(TestBSTSuite, OperatorAssignmentAnotherTree)
{
    BinarySearchTree<int> another = {3, 1, 2, 5, 4};
    BinarySearchTree<int> testObj = another;
    EXPECT_FALSE(testObj.empty());
    EXPECT_FALSE(testObj.get_root() == nullptr);
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_TRUE(testObj.is_valid());

    BinarySearchTree<int> another2 = {3, 1, 2, 5, 4, 7, 6};
    testObj = another2;
    EXPECT_FALSE(testObj.empty());
    EXPECT_FALSE(testObj.get_root() == nullptr);
    EXPECT_EQ(testObj.size(), 7U);
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

    testObj = another;
    EXPECT_TRUE(testObj == another);
}

TEST_F(TestBSTSuite, MethodIsSameSet)
{
    BinarySearchTree<int> testObj = {3, 3, 3, 1, 1, 2, 2, 2, 2};
    BinarySearchTree<int> another = {1, 1, 2, 2, 2, 2, 3, 3, 3};

    EXPECT_TRUE(testObj.is_same_set(another));

    another = {1, 2, 2, 2, 2, 3, 3, 3};
    EXPECT_FALSE(testObj.is_same_set(another));
    
    another = {1, 2, 3, 4, 5};
    EXPECT_FALSE(testObj.is_same_set(another));
}

TEST_F(TestBSTSuite, MethodSwap)
{
    BinarySearchTree<int> testObj;
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.get_root() == nullptr);
    EXPECT_TRUE(testObj.is_valid());

    BinarySearchTree<int> another = {3, 1, 2, 5, 4};
    testObj.swap(another);
    EXPECT_FALSE(testObj.empty());
    EXPECT_FALSE(testObj.get_root() == nullptr);
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_TRUE(testObj.is_valid());

    testObj.swap(another);
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.get_root() == nullptr);
    EXPECT_TRUE(testObj.is_valid());
}

TEST_F(TestBSTSuite, MethodGetNode)
{
    BinarySearchTree<int> testObj;
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.get_root() == nullptr);
    EXPECT_TRUE(testObj.is_valid());

    const BinarySearchTree<int>::Node* node = testObj.get_node(1);
    EXPECT_TRUE(node == nullptr);

    testObj.insert(1);
    node = testObj.get_node(1);
    EXPECT_TRUE(node != nullptr);
    EXPECT_EQ(node->data, 1);
    EXPECT_EQ(node->count, 1U);

    testObj.insert(1);
    node = testObj.get_node(1);
    EXPECT_TRUE(node != nullptr);
    EXPECT_EQ(node->data, 1);
    EXPECT_EQ(node->count, 2U);

    testObj.insert(2);
    testObj.insert(5);
    testObj.insert(1);
    testObj.insert(3);
    node = testObj.get_node(10);
    EXPECT_TRUE(node == nullptr);

    node = testObj.get_node(1);
    EXPECT_EQ(node->data, 1);
    EXPECT_EQ(node->count, 3U);

    node = testObj.get_node(3);
    EXPECT_EQ(node->data, 3);
    EXPECT_EQ(node->count, 1U);
}

TEST_F(TestBSTSuite, MethodGetMinNode)
{
    BinarySearchTree<int> testObj;
    EXPECT_TRUE(testObj.get_min_node() == nullptr);

    testObj.insert(1);
    EXPECT_EQ(testObj.get_min_node()->data, 1);

    testObj.insert(2);
    EXPECT_EQ(testObj.get_min_node()->data, 1);

    testObj.insert(0);
    EXPECT_EQ(testObj.get_min_node()->data, 0);
}

TEST_F(TestBSTSuite, MethodGetMaxNode)
{
    BinarySearchTree<int> testObj;
    EXPECT_TRUE(testObj.get_max_node() == nullptr);

    testObj.insert(1);
    EXPECT_EQ(testObj.get_max_node()->data, 1);

    testObj.insert(2);
    EXPECT_EQ(testObj.get_max_node()->data, 2);

    testObj.insert(0);
    EXPECT_EQ(testObj.get_max_node()->data, 2);
}

TEST_F(TestBSTSuite, MethodGetLowestCommonAncestor)
{
    BinarySearchTree<int> testObj = {5, 2, 7, 1, 4, 9};
    EXPECT_TRUE(testObj.get_lowest_common_ancestor(1, 3) == nullptr);

    EXPECT_EQ(testObj.get_lowest_common_ancestor(5, 5)->data, 5);
    EXPECT_EQ(testObj.get_lowest_common_ancestor(2, 7)->data, 5);
    EXPECT_EQ(testObj.get_lowest_common_ancestor(1, 7)->data, 5);
    EXPECT_EQ(testObj.get_lowest_common_ancestor(1, 4)->data, 2);
    EXPECT_EQ(testObj.get_lowest_common_ancestor(1, 9)->data, 5);
    EXPECT_EQ(testObj.get_lowest_common_ancestor(7, 9)->data, 7);
}

TEST_F(TestBSTSuite, MethodInsert)
{
    BinarySearchTree<int> testObj;
    testObj.insert(3);
    testObj.insert(1);
    testObj.insert(2);
    testObj.insert(5);
    testObj.insert(4);

    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 5U);
}

TEST_F(TestBSTSuite, MethodContain)
{
    BinarySearchTree<int> testObj;
    testObj.insert(3);
    testObj.insert(1);
    testObj.insert(2);
    testObj.insert(5);
    testObj.insert(4);

    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 5U);

    EXPECT_TRUE(testObj.contain(1));
    EXPECT_TRUE(testObj.contain(2));
    EXPECT_TRUE(testObj.contain(3));
    EXPECT_TRUE(testObj.contain(4));
    EXPECT_TRUE(testObj.contain(5));
    EXPECT_FALSE(testObj.contain(6));
}

TEST_F(TestBSTSuite, MethodErase)
{
    std::vector<std::pair<int, std::size_t>> elements;

    BinarySearchTree<int> testObj = {1, 1, 1, 2, 2, 3, 3, 3, 4, 5};
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 10U);

    testObj.erase(1);
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 7U);

    testObj.erase(3);
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 4U);

    testObj.erase(4);
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 3U);

    testObj.erase(6);
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 3U);

    testObj.erase(5);
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 2U);

    testObj.erase(2);
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestBSTSuite, MethodClear)
{
    BinarySearchTree<int> testObj;
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.get_root() == nullptr);
    EXPECT_TRUE(testObj.is_valid());

    testObj.insert(3);
    testObj.insert(1);
    testObj.insert(2);
    testObj.insert(5);
    testObj.insert(4);
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 5U);

    testObj.clear();
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.get_root() == nullptr);
    EXPECT_TRUE(testObj.is_valid());
}

TEST_F(TestBSTSuite, MethodTraversal)
{
    BinarySearchTree<int> testObj;

    std::vector<std::pair<int, std::size_t>> elements;
    elements = testObj.traversal();
    EXPECT_TRUE(elements.empty());

    testObj.insert(3);
    testObj.insert(1);
    testObj.insert(2);
    testObj.insert(5);
    testObj.insert(4);
    elements = testObj.traversal();
    for (std::pair<int, std::size_t> p : elements)
    {
        EXPECT_EQ(p.second, 1U);
    }

    testObj.insert(3);
    elements = testObj.traversal();
    EXPECT_EQ(elements[2].first, 3);
    EXPECT_EQ(elements[2].second, 2U);
}

TEST_F(TestBSTSuite, MethodHeight)
{
    BinarySearchTree<int> testObj;
    EXPECT_EQ(testObj.height(), 0U);

    testObj.insert(5);
    EXPECT_EQ(testObj.height(), 1U);

    testObj.insert(3);
    EXPECT_EQ(testObj.height(), 2U);

    testObj.insert(7);
    EXPECT_EQ(testObj.height(), 2U);

    testObj.insert(9);
    EXPECT_EQ(testObj.height(), 3U);

    testObj.insert(6);
    EXPECT_EQ(testObj.height(), 3U);

    testObj.insert(1);
    EXPECT_EQ(testObj.height(), 3U);

    testObj.insert(0);
    EXPECT_EQ(testObj.height(), 4U);
}