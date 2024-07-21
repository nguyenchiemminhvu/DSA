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
    UnweightedGraph<int> testObj;
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
    WeightedGraph<int> testObj;
}