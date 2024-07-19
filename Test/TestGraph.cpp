#include <gtest/gtest.h>

#include "Graph/Graph.h"

class TestUndirectedGraphSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestUndirectedGraphSuite, ConstructorDefault)
{
    UndirectedGraph<int> testObj;
}



class TestDirectedGraphSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestDirectedGraphSuite, ConstructorDefault)
{
    DirectedGraph<int> testObj;
}