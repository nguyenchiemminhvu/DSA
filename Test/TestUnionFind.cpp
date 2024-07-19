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

TEST_F(TestUnionFindSuite, ConstructorDefault)
{
    UnionFind testObj;
}

TEST_F(TestUnionFindSuite, MethodUnite)
{
    UnionFind testObj;
}

TEST_F(TestUnionFindSuite, MethodSameGroup)
{
    UnionFind testObj;
}
