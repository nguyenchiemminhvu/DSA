#include <gtest/gtest.h>

#include "Graph/Graph.h"

class TestDirectedGraph : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestDirectedGraph, ConstructorDefault)
{
    EXPECT_NO_FATAL_FAILURE(DirectedGraph testObj(7U));
}

TEST_F(TestDirectedGraph, MethodAddEdgeNoWeight)
{
    DirectedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U));

    EXPECT_THROW(testObj.add_edge(6U, 7U), std::out_of_range);
}

TEST_F(TestDirectedGraph, MethodAddEdge)
{
    DirectedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    EXPECT_THROW(testObj.add_edge(6U, 7U, 1U), std::out_of_range);
}

TEST_F(TestDirectedGraph, MethodHasEdge)
{
    DirectedGraph testObj(7U);

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

TEST_F(TestDirectedGraph, MethodRemoveEdge)
{
    DirectedGraph testObj(7U);

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

TEST_F(TestDirectedGraph, MethodIsConnected)
{
    DirectedGraph testObj(7U);

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

TEST_F(TestDirectedGraph, MethodHasCycle)
{
    DirectedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_FALSE(testObj.has_cycle());

    EXPECT_NO_THROW(testObj.add_edge(4U, 2U, 1U));
    EXPECT_TRUE(testObj.has_cycle());

    EXPECT_NO_THROW(testObj.remove_edge(2U, 3U));
    EXPECT_FALSE(testObj.has_cycle());

    EXPECT_NO_THROW(testObj.add_edge(2U, 4U, 1U));
    EXPECT_TRUE(testObj.has_cycle());
}

TEST_F(TestDirectedGraph, MethodTraversalBFS)
{
    DirectedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));

    std::vector<std::size_t> group = testObj.traversal_bfs(0U);
    std::sort(group.begin(), group.end());
    EXPECT_EQ(group[0U], 0U);
    EXPECT_EQ(group[1U], 1U);
    EXPECT_EQ(group[2U], 2U);
    EXPECT_EQ(group[3U], 3U);

    group = testObj.traversal_bfs(1U);
    std::sort(group.begin(), group.end());
    EXPECT_EQ(group[0U], 1U);
    EXPECT_EQ(group[1U], 2U);
    EXPECT_EQ(group[2U], 3U);
}

TEST_F(TestDirectedGraph, MethodTraversalDFS)
{
    DirectedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));

    std::vector<std::size_t> group = testObj.traversal_dfs(0U);
    std::sort(group.begin(), group.end());
    EXPECT_EQ(group[0U], 0U);
    EXPECT_EQ(group[1U], 1U);
    EXPECT_EQ(group[2U], 2U);
    EXPECT_EQ(group[3U], 3U);

    group = testObj.traversal_dfs(1U);
    std::sort(group.begin(), group.end());
    EXPECT_EQ(group[0U], 1U);
    EXPECT_EQ(group[1U], 2U);
    EXPECT_EQ(group[2U], 3U);
}

TEST_F(TestDirectedGraph, MethodConnectedComponents)
{
    DirectedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 0U, 1U));

    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 3U, 1U));

    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(6U, 5U, 1U));

    std::vector<std::vector<std::size_t>> components = testObj.connected_components();
    EXPECT_EQ(components.size(), 3U);
}

TEST_F(TestDirectedGraph, MethodDistance)
{
    DirectedGraph testObj(7U);

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

TEST_F(TestDirectedGraph, MethodShortestPath)
{
    DirectedGraph testObj(7U);

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

TEST_F(TestDirectedGraph, MethodReachableVertices)
{
    DirectedGraph testObj(7U);

    EXPECT_EQ(testObj.reachable_vertices(0U, 0U).size(), 1U);
    EXPECT_EQ(testObj.reachable_vertices(0U, 1U).size(), 1U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    std::unordered_set<std::size_t> reachable = testObj.reachable_vertices(0U, 1U);
    EXPECT_TRUE(reachable.find(0U) != reachable.end());
    EXPECT_TRUE(reachable.find(1U) != reachable.end());
    EXPECT_TRUE(reachable.find(2U) == reachable.end());

    reachable = testObj.reachable_vertices(0U, 2U);
    EXPECT_TRUE(reachable.find(0U) != reachable.end());
    EXPECT_TRUE(reachable.find(1U) != reachable.end());
    EXPECT_TRUE(reachable.find(2U) != reachable.end());
    EXPECT_TRUE(reachable.find(3U) == reachable.end());

    reachable = testObj.reachable_vertices(0U, 3U);
    EXPECT_TRUE(reachable.find(0U) != reachable.end());
    EXPECT_TRUE(reachable.find(1U) != reachable.end());
    EXPECT_TRUE(reachable.find(2U) != reachable.end());
    EXPECT_TRUE(reachable.find(3U) != reachable.end());
    EXPECT_TRUE(reachable.find(4U) == reachable.end());
}

TEST_F(TestDirectedGraph, MethodMinDistanceAllPairs)
{
    DirectedGraph testObj(7U);

    std::vector<std::vector<std::size_t>> min_dist = testObj.min_distance_all_pairs();
    for (std::size_t i = 0U; i < 7U; i++)
    {
        for (std::size_t j = 0U; j < 7U; j++)
        {
            if (i == j)
            {
                EXPECT_EQ(min_dist[i][j], 0U);
                EXPECT_EQ(min_dist[j][i], 0U);
            }
            else
            {
                EXPECT_EQ(min_dist[i][j], UNREACHABLE_DISTANCE);
                EXPECT_EQ(min_dist[j][i], UNREACHABLE_DISTANCE);
            }
        }
    }

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    min_dist = testObj.min_distance_all_pairs();

    EXPECT_EQ(min_dist[0U][1U], 1U);
    EXPECT_EQ(min_dist[1U][2U], 1U);
    EXPECT_EQ(min_dist[2U][3U], 1U);
    EXPECT_EQ(min_dist[3U][4U], 1U);
    EXPECT_EQ(min_dist[4U][5U], 1U);
    EXPECT_EQ(min_dist[5U][6U], 1U);

    EXPECT_EQ(min_dist[1U][0U], UNREACHABLE_DISTANCE);
    EXPECT_EQ(min_dist[2U][1U], UNREACHABLE_DISTANCE);
    EXPECT_EQ(min_dist[3U][2U], UNREACHABLE_DISTANCE);
    EXPECT_EQ(min_dist[4U][3U], UNREACHABLE_DISTANCE);
    EXPECT_EQ(min_dist[5U][4U], UNREACHABLE_DISTANCE);
    EXPECT_EQ(min_dist[6U][5U], UNREACHABLE_DISTANCE);

    EXPECT_EQ(min_dist[0U][2U], 2U);
    EXPECT_EQ(min_dist[2U][0U], UNREACHABLE_DISTANCE);

    EXPECT_EQ(min_dist[0U][6U], 6U);
    EXPECT_EQ(min_dist[6U][0U], UNREACHABLE_DISTANCE);
}

TEST_F(TestDirectedGraph, MethodTopologicalSort)
{
    DirectedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    std::vector<std::size_t> topo_sorted = testObj.topological_sort();
    EXPECT_TRUE(testObj.is_topologically_sorted(topo_sorted));
    for (std::size_t i = 1U; i < 7U; i++)
    {
        EXPECT_TRUE(topo_sorted[i] > topo_sorted[i - 1]);
    }
}

TEST_F(TestDirectedGraph, MethodIsTopologicallySorted)
{
    DirectedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    std::vector<std::size_t> sorted = {0U, 1U, 2U, 3U, 4U, 5U, 6U};
    EXPECT_TRUE(testObj.is_topologically_sorted(sorted));
}


class TestUndirectedGraph : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestUndirectedGraph, ConstructorDefault)
{
    EXPECT_NO_FATAL_FAILURE(UndirectedGraph testObj(7U));
}

TEST_F(TestUndirectedGraph, MethodAddEdgeNoWeight)
{
    UndirectedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U));

    EXPECT_THROW(testObj.add_edge(6U, 7U), std::out_of_range);
}


TEST_F(TestUndirectedGraph, MethodAddEdge)
{
    UndirectedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    EXPECT_THROW(testObj.add_edge(6U, 7U, 1U), std::out_of_range);
}

TEST_F(TestUndirectedGraph, MethodHasEdge)
{
    UndirectedGraph testObj(7U);

    EXPECT_FALSE(testObj.has_edge(0U, 1U));
    EXPECT_FALSE(testObj.has_edge(1U, 2U));
    EXPECT_FALSE(testObj.has_edge(2U, 3U));
    EXPECT_FALSE(testObj.has_edge(3U, 4U));
    EXPECT_FALSE(testObj.has_edge(4U, 5U));
    EXPECT_FALSE(testObj.has_edge(5U, 6U));

    EXPECT_NO_THROW(testObj.add_edge(1U, 0U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(6U, 5U, 1U));

    EXPECT_TRUE(testObj.has_edge(0U, 1U));
    EXPECT_TRUE(testObj.has_edge(1U, 2U));
    EXPECT_TRUE(testObj.has_edge(2U, 3U));
    EXPECT_TRUE(testObj.has_edge(3U, 4U));
    EXPECT_TRUE(testObj.has_edge(4U, 5U));
    EXPECT_TRUE(testObj.has_edge(5U, 6U));
}

TEST_F(TestUndirectedGraph, MethodRemoveEdge)
{
    UndirectedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    EXPECT_NO_THROW(testObj.remove_edge(1U, 0U));
    EXPECT_FALSE(testObj.has_edge(0U, 1U));

    EXPECT_NO_THROW(testObj.remove_edge(2U, 1U));
    EXPECT_FALSE(testObj.has_edge(1U, 2U));

    EXPECT_NO_THROW(testObj.remove_edge(3U, 2U));
    EXPECT_FALSE(testObj.has_edge(2U, 3U));

    EXPECT_NO_THROW(testObj.remove_edge(4U, 3U));
    EXPECT_FALSE(testObj.has_edge(3U, 4U));

    EXPECT_NO_THROW(testObj.remove_edge(5U, 4U));
    EXPECT_FALSE(testObj.has_edge(4U, 5U));

    EXPECT_NO_THROW(testObj.remove_edge(6U, 5U));
    EXPECT_FALSE(testObj.has_edge(5U, 6U));
}

TEST_F(TestUndirectedGraph, MethodIsConnected)
{
    UndirectedGraph testObj(7U);

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

TEST_F(TestUndirectedGraph, MethodHasCycle)
{
    UndirectedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_FALSE(testObj.has_cycle());

    EXPECT_NO_THROW(testObj.add_edge(2U, 4U, 1U));
    EXPECT_TRUE(testObj.has_cycle());

    EXPECT_NO_THROW(testObj.remove_edge(2U, 3U));
    EXPECT_FALSE(testObj.has_cycle());

    EXPECT_NO_THROW(testObj.add_edge(0U, 3U));
    EXPECT_TRUE(testObj.has_cycle());
}

TEST_F(TestUndirectedGraph, MethodTraversalBFS)
{
    UndirectedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));

    std::vector<std::size_t> group = testObj.traversal_bfs(0U);
    std::sort(group.begin(), group.end());
    EXPECT_EQ(group[0U], 0U);
    EXPECT_EQ(group[1U], 1U);
    EXPECT_EQ(group[2U], 2U);
    EXPECT_EQ(group[3U], 3U);

    group = testObj.traversal_bfs(1U);
    std::sort(group.begin(), group.end());
    EXPECT_EQ(group[0U], 0U);
    EXPECT_EQ(group[1U], 1U);
    EXPECT_EQ(group[2U], 2U);
    EXPECT_EQ(group[3U], 3U);
}

TEST_F(TestUndirectedGraph, MethodTraversalDFS)
{
    UndirectedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));

    std::vector<std::size_t> group = testObj.traversal_dfs(0U);
    std::sort(group.begin(), group.end());
    EXPECT_EQ(group[0U], 0U);
    EXPECT_EQ(group[1U], 1U);
    EXPECT_EQ(group[2U], 2U);
    EXPECT_EQ(group[3U], 3U);

    group = testObj.traversal_dfs(1U);
    std::sort(group.begin(), group.end());
    EXPECT_EQ(group[0U], 0U);
    EXPECT_EQ(group[1U], 1U);
    EXPECT_EQ(group[2U], 2U);
    EXPECT_EQ(group[3U], 3U);
}

TEST_F(TestUndirectedGraph, MethodConnectedComponents)
{
    UndirectedGraph testObj(7U);
    
    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));

    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    std::vector<std::vector<std::size_t>> components = testObj.connected_components();
    EXPECT_EQ(components.size(), 2U);

    EXPECT_NO_THROW(testObj.remove_edge(2U, 3U));
    components = testObj.connected_components();
    EXPECT_EQ(components.size(), 3U);

    std::size_t count_vertex = 0U;
    for (const std::vector<std::size_t>& component : components)
    {
        count_vertex += component.size();
    }
    EXPECT_EQ(count_vertex, 7U);
}

TEST_F(TestUndirectedGraph, MethodDistance)
{
    UndirectedGraph testObj(7U);

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

TEST_F(TestUndirectedGraph, MethodShortestPath)
{
    UndirectedGraph testObj(7U);

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

TEST_F(TestUndirectedGraph, MethodReachableVertices)
{
    UndirectedGraph testObj(7U);

    EXPECT_EQ(testObj.reachable_vertices(0U, 0U).size(), 1U);
    EXPECT_EQ(testObj.reachable_vertices(0U, 1U).size(), 1U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    std::unordered_set<std::size_t> reachable = testObj.reachable_vertices(0U, 1U);
    EXPECT_TRUE(reachable.find(0U) != reachable.end());
    EXPECT_TRUE(reachable.find(1U) != reachable.end());
    EXPECT_TRUE(reachable.find(2U) == reachable.end());

    reachable = testObj.reachable_vertices(0U, 2U);
    EXPECT_TRUE(reachable.find(0U) != reachable.end());
    EXPECT_TRUE(reachable.find(1U) != reachable.end());
    EXPECT_TRUE(reachable.find(2U) != reachable.end());
    EXPECT_TRUE(reachable.find(3U) == reachable.end());

    reachable = testObj.reachable_vertices(0U, 3U);
    EXPECT_TRUE(reachable.find(0U) != reachable.end());
    EXPECT_TRUE(reachable.find(1U) != reachable.end());
    EXPECT_TRUE(reachable.find(2U) != reachable.end());
    EXPECT_TRUE(reachable.find(3U) != reachable.end());
    EXPECT_TRUE(reachable.find(4U) == reachable.end());
}

TEST_F(TestUndirectedGraph, MethodMinDistanceAllPairs)
{
    UndirectedGraph testObj(7U);

    std::vector<std::vector<std::size_t>> min_dist = testObj.min_distance_all_pairs();
    for (std::size_t i = 0U; i < 7U; i++)
    {
        for (std::size_t j = 0U; j < 7U; j++)
        {
            if (i == j)
            {
                EXPECT_EQ(min_dist[i][j], 0U);
                EXPECT_EQ(min_dist[j][i], 0U);
            }
            else
            {
                EXPECT_EQ(min_dist[i][j], UNREACHABLE_DISTANCE);
                EXPECT_EQ(min_dist[j][i], UNREACHABLE_DISTANCE);
            }
        }
    }

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    min_dist = testObj.min_distance_all_pairs();

    EXPECT_EQ(min_dist[0U][1U], 1U);
    EXPECT_EQ(min_dist[1U][2U], 1U);
    EXPECT_EQ(min_dist[2U][3U], 1U);
    EXPECT_EQ(min_dist[3U][4U], 1U);
    EXPECT_EQ(min_dist[4U][5U], 1U);
    EXPECT_EQ(min_dist[5U][6U], 1U);

    EXPECT_EQ(min_dist[1U][0U], 1U);
    EXPECT_EQ(min_dist[2U][1U], 1U);
    EXPECT_EQ(min_dist[3U][2U], 1U);
    EXPECT_EQ(min_dist[4U][3U], 1U);
    EXPECT_EQ(min_dist[5U][4U], 1U);
    EXPECT_EQ(min_dist[6U][5U], 1U);

    EXPECT_EQ(min_dist[0U][2U], 2U);
    EXPECT_EQ(min_dist[2U][0U], 2U);

    EXPECT_EQ(min_dist[0U][6U], 6U);
    EXPECT_EQ(min_dist[6U][0U], 6U);
}

TEST_F(TestUndirectedGraph, MethodMinSpanningTreeKruskal)
{
    UndirectedGraph testObj(7U);

    std::vector<std::pair<std::size_t, std::pair<std::size_t, std::size_t>>> min_spanning_tree = testObj.min_spanning_tree_kruskal();
    EXPECT_EQ(min_spanning_tree.size(), 0U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    min_spanning_tree = testObj.min_spanning_tree_kruskal();
    EXPECT_EQ(min_spanning_tree.size(), 6U);

    for (const std::pair<std::size_t, std::pair<std::size_t, std::size_t>>& edge : min_spanning_tree)
    {
        EXPECT_EQ(edge.first, 1U);
    }

    EXPECT_NO_THROW(testObj.remove_edge(2U, 3U));
    min_spanning_tree = testObj.min_spanning_tree_kruskal();
    EXPECT_EQ(min_spanning_tree.size(), 0U);
}

TEST_F(TestUndirectedGraph, MethodMinSpanningTreePrim)
{
    UndirectedGraph testObj(7U);

    std::vector<std::pair<std::size_t, std::pair<std::size_t, std::size_t>>> min_spanning_tree = testObj.min_spanning_tree_prim();
    EXPECT_EQ(min_spanning_tree.size(), 0U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    min_spanning_tree = testObj.min_spanning_tree_prim();
    EXPECT_EQ(min_spanning_tree.size(), 6U);

    for (const std::pair<std::size_t, std::pair<std::size_t, std::size_t>>& edge : min_spanning_tree)
    {
        EXPECT_EQ(edge.first, 1U);
    }

    EXPECT_NO_THROW(testObj.remove_edge(2U, 3U));
    min_spanning_tree = testObj.min_spanning_tree_prim();
    EXPECT_EQ(min_spanning_tree.size(), 0U);
}

TEST_F(TestUndirectedGraph, MethodFindBridges)
{
    UndirectedGraph testObj(9U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    EXPECT_NO_THROW(testObj.add_edge(6U, 7U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(7U, 8U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(8U, 6U, 1U));

    std::vector<std::pair<std::size_t, std::size_t>> bridges = testObj.find_bridges();
    EXPECT_EQ(bridges.size(), 6U);

    std::sort(bridges.begin(), bridges.end());
    for (std::size_t i = 0U; i < 6U; i++)
    {
        EXPECT_EQ(bridges[i].first, i);
        EXPECT_EQ(bridges[i].second, i + 1);
    }
}

TEST_F(TestUndirectedGraph, MethodFindArticulationPoints)
{
    UndirectedGraph testObj(9U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    EXPECT_NO_THROW(testObj.add_edge(6U, 7U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(7U, 8U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(8U, 6U, 1U));

    std::vector<std::size_t> articulation = testObj.find_articulation_points();

    EXPECT_EQ(articulation.size(), 6U);

    std::sort(articulation.begin(), articulation.end());
    for (std::size_t i = 0U; i < 6U; i++)
    {
        EXPECT_EQ(articulation[i], i + 1);
    }
}

TEST_F(TestUndirectedGraph, MethodColoringGraph)
{
    UndirectedGraph testObj(7U);

    EXPECT_NO_THROW(testObj.add_edge(0U, 1U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(1U, 2U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(2U, 3U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(3U, 4U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(4U, 5U, 1U));
    EXPECT_NO_THROW(testObj.add_edge(5U, 6U, 1U));

    std::vector<std::size_t> color_map = testObj.coloring_graph();
    std::unordered_set<std::size_t> color_set(color_map.begin(), color_map.end());
    EXPECT_EQ(color_set.size(), 2U);
}
