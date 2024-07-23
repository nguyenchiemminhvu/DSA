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
    EXPECT_NO_FATAL_FAILURE(UnweightedGraph testObj(7U));
}

TEST_F(TestUnweightedGraphSuite, MethodAddEdge)
{
    UnweightedGraph testObj(7U);
    EXPECT_NO_THROW(testObj.add_edge(0U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U));

    EXPECT_THROW(testObj.add_edge(6U, 7U), std::out_of_range);
}

TEST_F(TestUnweightedGraphSuite, MethodHasEdge)
{
    UnweightedGraph testObj(7U);

    EXPECT_FALSE(testObj.has_edge(0U, 1U));
    EXPECT_FALSE(testObj.has_edge(1U, 2U));
    EXPECT_FALSE(testObj.has_edge(2U, 3U));
    EXPECT_FALSE(testObj.has_edge(3U, 4U));
    EXPECT_FALSE(testObj.has_edge(4U, 5U));
    EXPECT_FALSE(testObj.has_edge(5U, 6U));

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U));

    EXPECT_TRUE(testObj.has_edge(0U, 1U));
    EXPECT_TRUE(testObj.has_edge(1U, 2U));
    EXPECT_TRUE(testObj.has_edge(2U, 3U));
    EXPECT_TRUE(testObj.has_edge(3U, 4U));
    EXPECT_TRUE(testObj.has_edge(4U, 5U));
    EXPECT_TRUE(testObj.has_edge(5U, 6U));
}

TEST_F(TestUnweightedGraphSuite, MethodRemoveEdge)
{
    UnweightedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U));

    EXPECT_NO_THROW(testObj.remove_edge(0U, 1U));
    EXPECT_FALSE(testObj.has_edge(0U, 1U));

    EXPECT_NO_THROW(testObj.remove_edge(1U, 2U));
    EXPECT_FALSE(testObj.has_edge(1U, 2U));

    EXPECT_NO_THROW(testObj.remove_edge(2U, 3U));
    EXPECT_FALSE(testObj.has_edge(2U, 3U));

    EXPECT_NO_THROW(testObj.remove_edge(3U, 4U));
    EXPECT_FALSE(testObj.has_edge(3U, 4U));

    EXPECT_NO_THROW(testObj.remove_edge(4U, 5U));
    EXPECT_FALSE(testObj.has_edge(4U, 5U));

    EXPECT_NO_THROW(testObj.remove_edge(5U, 6U));
    EXPECT_FALSE(testObj.has_edge(5U, 6U));
}

TEST_F(TestUnweightedGraphSuite, MethodIsConnected)
{
    UnweightedGraph testObj(7U);

    EXPECT_FALSE(testObj.is_connected(0U, 1U));
    EXPECT_FALSE(testObj.is_connected(2U, 4U));

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U));
    EXPECT_TRUE(testObj.is_connected(0U, 1U));

    EXPECT_NO_THROW(testObj.add_edge(2U, 5U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 3U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U));
    EXPECT_TRUE(testObj.is_connected(2U, 4U));

    EXPECT_TRUE(testObj.is_connected(6U, 6U));
}

TEST_F(TestUnweightedGraphSuite, MethodDistance)
{
    UnweightedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U));

    EXPECT_EQ(testObj.distance(0U, 0U), 0U);
    EXPECT_EQ(testObj.distance(0U, 1U), 1U);
    EXPECT_EQ(testObj.distance(0U, 2U), 2U);
    EXPECT_EQ(testObj.distance(0U, 3U), 3U);
    EXPECT_EQ(testObj.distance(0U, 4U), 4U);
    EXPECT_EQ(testObj.distance(0U, 5U), 5U);
    EXPECT_EQ(testObj.distance(0U, 6U), 6U);

    EXPECT_THROW(testObj.distance(0U, 7U), std::out_of_range);
}

TEST_F(TestUnweightedGraphSuite, MethodShortestPath)
{
    UnweightedGraph testObj(7U);

    EXPECT_EQ(testObj.shortest_path(0U, 0U).size(), 1U);
    EXPECT_EQ(testObj.shortest_path(0U, 1U).size(), 0U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U));

    std::vector<std::size_t> path = testObj.shortest_path(0U, 6U);

    for (std::size_t i = 0U; i < path.size(); i++)
    {
        EXPECT_EQ(path[i], i);
    }
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
    EXPECT_NO_FATAL_FAILURE(WeightedGraph testObj(7U));
}

TEST_F(TestWeightedGraphSuite, MethodAddEdge)
{
    WeightedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    EXPECT_THROW(testObj.add_edge(6U, 7U, 1U), std::out_of_range);
}

TEST_F(TestWeightedGraphSuite, MethodHasEdge)
{
    WeightedGraph testObj(7U);

    EXPECT_FALSE(testObj.has_edge(0U, 1U));
    EXPECT_FALSE(testObj.has_edge(1U, 2U));
    EXPECT_FALSE(testObj.has_edge(2U, 3U));
    EXPECT_FALSE(testObj.has_edge(3U, 4U));
    EXPECT_FALSE(testObj.has_edge(4U, 5U));
    EXPECT_FALSE(testObj.has_edge(5U, 6U));

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    EXPECT_TRUE(testObj.has_edge(0U, 1U));
    EXPECT_TRUE(testObj.has_edge(1U, 2U));
    EXPECT_TRUE(testObj.has_edge(2U, 3U));
    EXPECT_TRUE(testObj.has_edge(3U, 4U));
    EXPECT_TRUE(testObj.has_edge(4U, 5U));
    EXPECT_TRUE(testObj.has_edge(5U, 6U));
}

TEST_F(TestWeightedGraphSuite, MethodRemoveEdge)
{
    WeightedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    EXPECT_NO_THROW(testObj.remove_edge(0U, 1U));
    EXPECT_FALSE(testObj.has_edge(0U, 1U));

    EXPECT_NO_THROW(testObj.remove_edge(1U, 2U));
    EXPECT_FALSE(testObj.has_edge(1U, 2U));

    EXPECT_NO_THROW(testObj.remove_edge(2U, 3U));
    EXPECT_FALSE(testObj.has_edge(2U, 3U));

    EXPECT_NO_THROW(testObj.remove_edge(3U, 4U));
    EXPECT_FALSE(testObj.has_edge(3U, 4U));

    EXPECT_NO_THROW(testObj.remove_edge(4U, 5U));
    EXPECT_FALSE(testObj.has_edge(4U, 5U));

    EXPECT_NO_THROW(testObj.remove_edge(5U, 6U));
    EXPECT_FALSE(testObj.has_edge(5U, 6U));
}

TEST_F(TestWeightedGraphSuite, MethodIsConnected)
{
    WeightedGraph testObj(7U);

    EXPECT_FALSE(testObj.is_connected(0U, 1U));
    EXPECT_FALSE(testObj.is_connected(2U, 4U));

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_TRUE(testObj.is_connected(0U, 1U));

    EXPECT_NO_THROW(testObj.add_edge(2U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_TRUE(testObj.is_connected(2U, 4U));

    EXPECT_TRUE(testObj.is_connected(6U, 6U));
}

TEST_F(TestWeightedGraphSuite, MethodDistance)
{
    WeightedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    EXPECT_EQ(testObj.distance(0U, 1U), 1U);
    EXPECT_EQ(testObj.distance(0U, 2U), 2U);
    EXPECT_EQ(testObj.distance(0U, 3U), 3U);
    EXPECT_EQ(testObj.distance(0U, 4U), 4U);
    EXPECT_EQ(testObj.distance(0U, 5U), 5U);
    EXPECT_EQ(testObj.distance(0U, 6U), 6U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 6U, 4U));
    EXPECT_EQ(testObj.distance(0U, 6U), 4U);

    EXPECT_THROW(testObj.distance(0U, 7U), std::out_of_range);
}

TEST_F(TestWeightedGraphSuite, MethodShortestPath)
{
    WeightedGraph testObj(7U);

    EXPECT_EQ(testObj.shortest_path(0U, 0U).size(), 1U);
    EXPECT_EQ(testObj.shortest_path(0U, 1U).size(), 0U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    std::vector<std::size_t> path = testObj.shortest_path(0U, 6U);
    for (std::size_t i = 0U; i < path.size(); i++)
    {
        EXPECT_EQ(path[i], i);
    }

    EXPECT_NO_THROW(testObj.add_edge(0U, 6U, 4U));
    path = testObj.shortest_path(0U, 6U);
    EXPECT_EQ(path[0], 0U);
    EXPECT_EQ(path[1], 6U);
}
