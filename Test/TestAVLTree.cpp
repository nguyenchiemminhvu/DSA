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
    EXPECT_EQ(testObj.size_set(), 0U);

    testObj.insert(5);
    EXPECT_FALSE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 1U);
    EXPECT_EQ(testObj.size_set(), 1U);

    testObj.insert(5);
    EXPECT_FALSE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 2U);
    EXPECT_EQ(testObj.size_set(), 1U);
    
    testObj.insert(1);
    EXPECT_FALSE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 3U);
    EXPECT_EQ(testObj.size_set(), 2U);
    
    testObj.insert(9);
    EXPECT_FALSE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 4U);
    EXPECT_EQ(testObj.size_set(), 3U);
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

TEST_F(TestAVLSuite, MethodCount)
{
    AVLTree<int> testObj;
    EXPECT_EQ(testObj.count(5), 0U);

    testObj.insert(5);
    EXPECT_EQ(testObj.count(5), 1U);

    testObj.insert(5);
    EXPECT_EQ(testObj.count(5), 2U);

    testObj.insert(1);
    EXPECT_EQ(testObj.count(1), 1U);

    testObj.insert(7);
    EXPECT_EQ(testObj.count(7), 1U);

    EXPECT_EQ(testObj.count(0), 0U);
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
    EXPECT_EQ(testObj.size_set(), 0U);

    testObj.erase(5);
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.size_set(), 0U);

    testObj.insert(5);
    testObj.erase(5);
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.size_set(), 0U);

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

    EXPECT_EQ(testObj.size(), 10U);
    EXPECT_EQ(testObj.size_set(), 10U);

    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ(testObj.size(), 10 - i);
        testObj.erase(i);
        EXPECT_TRUE(testObj.is_valid());
    }

    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestAVLSuite, MethodClear)
{
    AVLTree<int> testObj;
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

    testObj.clear();
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 0U);
}

TEST_F(TestAVLSuite, MethodTraversal)
{
    std::vector<std::pair<int, std::size_t>> elements;

    AVLTree<int> testObj;
    elements = testObj.traversal();
    EXPECT_EQ(elements.size(), 0U);

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
    EXPECT_TRUE(testObj.is_valid());

    elements = testObj.traversal();
    EXPECT_EQ(elements.size(), 10U);
    int cur_val = 0;
    for (const std::pair<int, std::size_t>& p : elements)
    {
        EXPECT_EQ(p.first, cur_val++);
        EXPECT_EQ(p.second, 1U);
    }
    
    testObj.insert(1);
    elements = testObj.traversal();
    EXPECT_EQ(elements[1].second, 2U);
}

TEST_F(TestAVLSuite, MethodGetMinNode)
{
    AVLTree<int> testObj;
    EXPECT_TRUE(testObj.get_min_node() == nullptr);

    testObj.insert(5);
    EXPECT_EQ(testObj.get_min_node()->data, 5);

    testObj.insert(7);
    EXPECT_EQ(testObj.get_min_node()->data, 5);

    testObj.insert(2);
    EXPECT_EQ(testObj.get_min_node()->data, 2);

    testObj.insert(3);
    EXPECT_EQ(testObj.get_min_node()->data, 2);

    testObj.insert(1);
    EXPECT_EQ(testObj.get_min_node()->data, 1);
}

TEST_F(TestAVLSuite, MethodGetMaxNode)
{
    AVLTree<int> testObj;
    EXPECT_TRUE(testObj.get_max_node() == nullptr);

    testObj.insert(5);
    EXPECT_EQ(testObj.get_max_node()->data, 5);

    testObj.insert(3);
    EXPECT_EQ(testObj.get_max_node()->data, 5);

    testObj.insert(7);
    EXPECT_EQ(testObj.get_max_node()->data, 7);
    
    testObj.insert(6);
    EXPECT_EQ(testObj.get_max_node()->data, 7);

    testObj.insert(9);
    EXPECT_EQ(testObj.get_max_node()->data, 9);
}

TEST_F(TestAVLSuite, MethodGetLowestCommonAncestor)
{
    AVLTree<int> testObj;
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

    EXPECT_TRUE(testObj.get_lowest_common_ancestor(0, 9) != nullptr);
    EXPECT_TRUE(testObj.get_lowest_common_ancestor(3, 7) != nullptr);
    EXPECT_TRUE(testObj.get_lowest_common_ancestor(1, 6) != nullptr);
    EXPECT_TRUE(testObj.get_lowest_common_ancestor(5, 5) != nullptr);

    EXPECT_TRUE(testObj.get_lowest_common_ancestor(0, 10) == nullptr);
}
