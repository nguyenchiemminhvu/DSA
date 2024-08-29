#include <gtest/gtest.h>

#include "DisjointSet/UnionFind.h"

class TestUnionFindSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestUnionFindSuite, ConstructorWithNumElement)
{
    UnionFind testObj(5U);
    EXPECT_FALSE(testObj.same_group(0, 1));
    EXPECT_FALSE(testObj.same_group(1, 2));
    EXPECT_FALSE(testObj.same_group(2, 3));
    EXPECT_FALSE(testObj.same_group(3, 4));
    
    EXPECT_THROW(testObj.same_group(4, 5), std::out_of_range);
}

TEST_F(TestUnionFindSuite, MethodUnite)
{
    UnionFind testObj(5U);

    EXPECT_NO_THROW(testObj.unite(0, 1));
    EXPECT_NO_THROW(testObj.unite(2, 3));
    EXPECT_NO_THROW(testObj.unite(0, 3));

    EXPECT_THROW(testObj.unite(4, 5), std::out_of_range);
}

TEST_F(TestUnionFindSuite, MethodSameGroup)
{
    UnionFind testObj(5U);

    EXPECT_NO_THROW(testObj.unite(0, 1));
    EXPECT_NO_THROW(testObj.unite(2, 3));
    EXPECT_NO_THROW(testObj.unite(0, 3));

    EXPECT_TRUE(testObj.same_group(0, 1));
    EXPECT_TRUE(testObj.same_group(1, 2));
    EXPECT_TRUE(testObj.same_group(2, 3));
    EXPECT_TRUE(testObj.same_group(0, 3));
    EXPECT_TRUE(testObj.same_group(1, 3));

    EXPECT_THROW(testObj.same_group(3, 5), std::out_of_range);
}

TEST_F(TestUnionFindSuite, MethodClusterSize)
{
    UnionFind testObj(5U);

    EXPECT_NO_THROW(testObj.unite(0, 1));
    EXPECT_NO_THROW(testObj.unite(2, 3));
    EXPECT_NO_THROW(testObj.unite(0, 3));

    EXPECT_EQ(testObj.cluster_size(0), 4);

    EXPECT_THROW(testObj.cluster_size(5), std::out_of_range);
}

TEST_F(TestUnionFindSuite, MethodNumClusters)
{
    UnionFind testObj(5U);
    EXPECT_EQ(testObj.num_clusters(), 5);
    EXPECT_NO_THROW(testObj.unite(0, 1));
    EXPECT_EQ(testObj.num_clusters(), 4);
    EXPECT_NO_THROW(testObj.unite(2, 3));
    EXPECT_EQ(testObj.num_clusters(), 3);
    EXPECT_NO_THROW(testObj.unite(0, 3));
    EXPECT_EQ(testObj.num_clusters(), 2);
}