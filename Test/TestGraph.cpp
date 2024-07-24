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

TEST_F(TestUndirectedGraph, MethodMinSpanningTreePrim)
{
    UndirectedGraph testObj(7U);
}

TEST_F(TestUndirectedGraph, MethodMinSpanningTreeKruskal)
{
    UndirectedGraph testObj(7U);
}

TEST_F(TestUndirectedGraph, MethodMinDistanceAllPairs)
{
    UndirectedGraph testObj(7U);
}
