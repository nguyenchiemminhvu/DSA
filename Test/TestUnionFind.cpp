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
}

TEST_F(TestUnionFindSuite, MethodUnite)
{
    UnionFind testObj(5U);
}

TEST_F(TestUnionFindSuite, MethodSameGroup)
{
    UnionFind testObj(5U);
}
