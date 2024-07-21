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
    BinaryIndexedTree2D<int> testObj(10U, 10U);
}