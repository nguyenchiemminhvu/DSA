#include <gtest/gtest.h>

#include "Tree/AVLTree.h"

class TestAVLTreeSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestAVLTreeSuite, ConstructorDefault)
{
    AVLTree<int> testObj;
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());
}

TEST_F(TestAVLTreeSuite, ConstructorInitializerList)
{
    AVLTree<int> testObj = {3, 1, 2, 5, 4};
    EXPECT_FALSE(testObj.empty());
    EXPECT_FALSE(testObj.get_root() == nullptr);
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_TRUE(testObj.is_valid());
}

TEST_F(TestAVLTreeSuite, ConstructorAnotherTree)
{
    AVLTree<int> another = {5, 2, 6, 1, 8};
    AVLTree<int> testObj(another);
    EXPECT_FALSE(testObj.empty());
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_TRUE(testObj.is_valid());
}

TEST_F(TestAVLTreeSuite, OperatorAssignmentList)
{
    AVLTree<int> testObj = {5, 2, 6, 1, 8};
    EXPECT_FALSE(testObj.empty());
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_TRUE(testObj.is_valid());
}

TEST_F(TestAVLTreeSuite, OperatorAssignmentAnotherTree)
{
    AVLTree<int> another = {5, 2, 6, 1, 8};
    AVLTree<int> testObj = another;
    EXPECT_FALSE(testObj.empty());
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_TRUE(testObj.is_valid());
}

TEST_F(TestAVLTreeSuite, OperatorCompareEqual)
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

TEST_F(TestAVLTreeSuite, MethodIsSameSet)
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

TEST_F(TestAVLTreeSuite, MethodSwap)
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

TEST_F(TestAVLTreeSuite, MethodInsert)
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

TEST_F(TestAVLTreeSuite, MethodContain)
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

TEST_F(TestAVLTreeSuite, MethodCount)
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

TEST_F(TestAVLTreeSuite, MethodGetNode)
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

TEST_F(TestAVLTreeSuite, MethodErase)
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

TEST_F(TestAVLTreeSuite, MethodClear)
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

TEST_F(TestAVLTreeSuite, MethodTraversal)
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

TEST_F(TestAVLTreeSuite, MethodGetMinNode)
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

TEST_F(TestAVLTreeSuite, MethodGetMaxNode)
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

TEST_F(TestAVLTreeSuite, MethodGetLowestCommonAncestor)
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
    EXPECT_FALSE(testObj.contain(5));

    testObj.insert(5, 2);
    testObj.insert(1, 1);
    testObj.insert(2, 2);
    testObj.insert(3, 3);

    EXPECT_TRUE(testObj.contain(5));
    EXPECT_TRUE(testObj.contain(1));
    EXPECT_TRUE(testObj.contain(2));
    EXPECT_TRUE(testObj.contain(3));
    EXPECT_FALSE(testObj.contain(4));
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

TEST_F(TestAVLMapSuite, MethodAt)
{
    AVLMap<int, int> testObj;

    for (int i = 0; i < 10; i++)
    {
        testObj.insert(i, 1);
    }

    EXPECT_TRUE(testObj.is_valid());

    for (int i = 0; i < 10; i++)
    {
        int& temp = testObj.at(i);
        temp = 2;
    }

    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ(testObj.get_node(i)->value, 2);
    }

    EXPECT_THROW(testObj.at(10), std::out_of_range);
}

TEST_F(TestAVLMapSuite, OperatorAccessViaKey)
{
    AVLMap<int, int> testObj;

    for (int i = 0; i < 10; i++)
    {
        testObj.insert(i, 1);
    }

    EXPECT_TRUE(testObj.is_valid());

    for (int i = 0; i < 10; i++)
    {
        int& temp = testObj[i];
        temp = 2;
    }

    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ(testObj.get_node(i)->value, 2);
    }

    testObj[10] = 2;
    EXPECT_EQ(testObj[10], 2);
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
    EXPECT_TRUE(testObj.empty());
    EXPECT_TRUE(testObj.is_valid());

    for (int i = 0; i < 10; i++)
    {
        testObj.insert(i, 1);
    }
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_EQ(testObj.size(), 10U);

    testObj.clear();
    EXPECT_TRUE(testObj.is_valid());
    EXPECT_TRUE(testObj.empty());
}
