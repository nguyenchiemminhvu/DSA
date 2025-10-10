#include <gtest/gtest.h>

#include "Tree/BinaryIndexedTree.h"

class TestBinaryIndexedTreeSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestBinaryIndexedTreeSuite, ConstructorDefault)
{
    BinaryIndexedTree<int> testObj(10U);
    for (int i = 1; i <= 10; i++)
    {
        EXPECT_EQ(testObj.query_prefix_sum(i), 0);
    }
}

TEST_F(TestBinaryIndexedTreeSuite, ConstructorVector)
{
    std::vector<int> V = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    BinaryIndexedTree<int> testObj(V);

    int cur = 0;
    for (int i = 1; i <= 10; i++)
    {
        cur += i;
        EXPECT_EQ(testObj.query_prefix_sum(i), cur);
    }
}

TEST_F(TestBinaryIndexedTreeSuite, MethodUpdate)
{
    BinaryIndexedTree<int> testObj(10U);
    for (int i = 1; i <= 10; i++)
    {
        EXPECT_NO_THROW(testObj.update(i, 1));
    }

    EXPECT_THROW(testObj.update(-1, 1), std::out_of_range);
    EXPECT_THROW(testObj.update(11, 1), std::out_of_range);
}

TEST_F(TestBinaryIndexedTreeSuite, MethodQueryPrefixSum)
{
    BinaryIndexedTree<int> testObj(10U);
    for (int i = 1; i <= 10; i++)
    {
        EXPECT_NO_THROW(testObj.update(i, 1));
    }

    for (int i = 1; i <= 10; i++)
    {
        EXPECT_EQ(testObj.query_prefix_sum(i), i);
    }

    EXPECT_THROW(testObj.query_prefix_sum(-1), std::out_of_range);
    EXPECT_THROW(testObj.query_prefix_sum(11), std::out_of_range);
}

TEST_F(TestBinaryIndexedTreeSuite, MethodQueryRange)
{
    BinaryIndexedTree<int> testObj(10U);
    for (int i = 1; i <= 10; i++)
    {
        EXPECT_NO_THROW(testObj.update(i, 1));
    }

    for (int i = 1; i <= 10; i++)
    {
        EXPECT_EQ(testObj.query_range(1, i), i);
    }

    EXPECT_EQ(testObj.query_range(1, 3), 3);
    EXPECT_EQ(testObj.query_range(2, 3), 2);
    EXPECT_EQ(testObj.query_range(3, 3), 1);

    EXPECT_THROW(testObj.query_range(-1, 1), std::out_of_range);
    EXPECT_THROW(testObj.query_range(2, 1), std::out_of_range);
    EXPECT_THROW(testObj.query_range(1, 11), std::out_of_range);
}


class TestBinaryIndexedTree2DSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestBinaryIndexedTree2DSuite, ConstructorDefault)
{
    BinaryIndexedTree2D<int> testObj(3U, 3U);
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            EXPECT_EQ(testObj.query_prefix_sum(i, j), 0);
        }
    }
}

TEST_F(TestBinaryIndexedTree2DSuite, ConstructorVector2D)
{
    std::vector<std::vector<int>> v = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    BinaryIndexedTree2D<int> testObj(v);
    EXPECT_EQ(testObj.query_prefix_sum(1, 1), 1);
    EXPECT_EQ(testObj.query_prefix_sum(2, 2), 4);
    EXPECT_EQ(testObj.query_prefix_sum(3, 3), 9);
}

TEST_F(TestBinaryIndexedTree2DSuite, MethodUpdate)
{
    BinaryIndexedTree2D<int> testObj(3U, 3U);
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            EXPECT_NO_THROW(testObj.update(i, j, 1));
        }
    }

    EXPECT_EQ(testObj.query_prefix_sum(1, 1), 1);
    EXPECT_EQ(testObj.query_prefix_sum(1, 2), 2);
    EXPECT_EQ(testObj.query_prefix_sum(2, 1), 2);
    EXPECT_EQ(testObj.query_prefix_sum(1, 3), 3);
    EXPECT_EQ(testObj.query_prefix_sum(3, 1), 3);
    EXPECT_EQ(testObj.query_prefix_sum(2, 2), 4);
    EXPECT_EQ(testObj.query_prefix_sum(2, 3), 6);
    EXPECT_EQ(testObj.query_prefix_sum(3, 2), 6);
    EXPECT_EQ(testObj.query_prefix_sum(3, 3), 9);

    EXPECT_THROW(testObj.update(-1, 1, 1), std::out_of_range);
    EXPECT_THROW(testObj.update(1, 11, 1), std::out_of_range);
    EXPECT_THROW(testObj.update(1, -1, 1), std::out_of_range);
    EXPECT_THROW(testObj.update(11, 1, 1), std::out_of_range);
}

TEST_F(TestBinaryIndexedTree2DSuite, MethodQueryPrefixSum)
{
    std::vector<std::vector<int>> v = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    BinaryIndexedTree2D<int> testObj(v);
    EXPECT_EQ(testObj.query_prefix_sum(1, 1), 1);
    EXPECT_EQ(testObj.query_prefix_sum(1, 2), 2);
    EXPECT_EQ(testObj.query_prefix_sum(2, 1), 2);
    EXPECT_EQ(testObj.query_prefix_sum(1, 3), 3);
    EXPECT_EQ(testObj.query_prefix_sum(3, 1), 3);
    EXPECT_EQ(testObj.query_prefix_sum(2, 2), 4);
    EXPECT_EQ(testObj.query_prefix_sum(2, 3), 6);
    EXPECT_EQ(testObj.query_prefix_sum(3, 2), 6);
    EXPECT_EQ(testObj.query_prefix_sum(3, 3), 9);

    EXPECT_THROW(testObj.query_prefix_sum(-1, 1), std::out_of_range);
    EXPECT_THROW(testObj.query_prefix_sum(1, 11), std::out_of_range);
    EXPECT_THROW(testObj.query_prefix_sum(1, -1), std::out_of_range);
    EXPECT_THROW(testObj.query_prefix_sum(11, 1), std::out_of_range);
}

TEST_F(TestBinaryIndexedTree2DSuite, MethodQueryRange)
{
    std::vector<std::vector<int>> v = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    BinaryIndexedTree2D<int> testObj(v);

    EXPECT_EQ(testObj.query_range(1, 1, 1, 1), 1);
    EXPECT_EQ(testObj.query_range(1, 1, 2, 2), 4);
    EXPECT_EQ(testObj.query_range(2, 2, 3, 3), 4);
    EXPECT_EQ(testObj.query_range(1, 1, 3, 3), 9);

    EXPECT_THROW(testObj.query_range(-1, 1, 1, 1), std::out_of_range);
    EXPECT_THROW(testObj.query_range(2, 1, 1, 1), std::out_of_range);
    EXPECT_THROW(testObj.query_range(1, 11, 1, 1), std::out_of_range);
    EXPECT_THROW(testObj.query_range(1, -1, 1, 1), std::out_of_range);
    EXPECT_THROW(testObj.query_range(1, 2, 1, 1), std::out_of_range);
    EXPECT_THROW(testObj.query_range(1, 1, 1, 11), std::out_of_range);
}
