#include <gtest/gtest.h>

#include "Graph/Graph.h"

class TestUnweightedGraphSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestUnweightedGraphSuite, ConstructorDefault)
{
    UnweightedGraph testObj(7U);
}

TEST_F(TestUnweightedGraphSuite, MethodAddEdge)
{
    UnweightedGraph testObj(7U);
}

TEST_F(TestUnweightedGraphSuite, MethodHasEdge)
{
    UnweightedGraph testObj(7U);
}

TEST_F(TestUnweightedGraphSuite, MethodRemoveEdge)
{
    UnweightedGraph testObj(7U);
}

TEST_F(TestUnweightedGraphSuite, MethodIsConnected)
{
    UnweightedGraph testObj(7U);
}

TEST_F(TestUnweightedGraphSuite, MethodDistance)
{
    UnweightedGraph testObj(7U);
}

TEST_F(TestUnweightedGraphSuite, MethodShortestPath)
{
    UnweightedGraph testObj(7U);
}



class TestWeightedGraphSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestWeightedGraphSuite, ConstructorDefault)
{
    WeightedGraph testObj(7U);
}