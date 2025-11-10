## Problem

https://leetcode.com/problems/find-if-path-exists-in-graph/description/

```
There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1 (inclusive). The edges in the graph are represented as a 2D integer array edges, where each edges[i] = [ui, vi] denotes a bi-directional edge between vertex ui and vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself.

You want to determine if there is a valid path that exists from vertex source to vertex destination.

Given edges and the integers n, source, and destination, return true if there is a valid path from source to destination, or false otherwise.

Example 1:

Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
Output: true
Explanation: There are two paths from vertex 0 to vertex 2:
- 0 → 1 → 2
- 0 → 2

Example 2:

Input: n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
Output: false
Explanation: There is no path from vertex 0 to vertex 5.

Constraints:

1 <= n <= 2 * 105
0 <= edges.length <= 2 * 105
edges[i].length == 2
0 <= ui, vi <= n - 1
ui != vi
0 <= source, destination <= n - 1
There are no duplicate edges.
There are no self edges.
```

## Observations

1. **Graph Connectivity Problem**: This is essentially asking whether two nodes are in the same connected component of an undirected graph.

2. **Bi-directional Edges**: Since all edges are bi-directional, we can traverse in both directions between connected vertices.

3. **Multiple Solutions Possible**:
   - **DFS/BFS**: Build adjacency list and traverse from source to find destination
   - **Union-Find (Disjoint Set Union)**: Group connected components and check if source and destination belong to the same group

4. **Union-Find Advantages**: 
   - More efficient for multiple connectivity queries
   - O(α(n)) amortized time per operation where α is inverse Ackermann function
   - Cleaner code for this specific problem

5. **Edge Cases**:
   - Source equals destination (should return true)
   - No edges (isolated vertices)
   - Single vertex graph

## Solution

**Approach: Union-Find (Disjoint Set Union)**

The solution uses Union-Find data structure to efficiently determine if two vertices are connected:

1. **Initialize DSU**: Create disjoint sets for all vertices (initially each vertex is its own parent)

2. **Union Operations**: For each edge [u, v], union the sets containing u and v

3. **Find Connection**: Check if source and destination have the same root (belong to same connected component)

**Key Components**:
- `find(x)`: Find root of vertex x with path compression optimization
- `unite(x, y)`: Merge sets containing x and y using union by rank
- Path compression and union by rank ensure nearly O(1) operations

**Time Complexity**: O(E × α(n)) where E is number of edges and α is inverse Ackermann function
**Space Complexity**: O(n) for parent and rank arrays

**Alternative Approaches**:
- DFS: O(V + E) time, simpler but less efficient for multiple queries
- BFS: O(V + E) time, good for finding shortest path but overkill here

# Tags

`Union-Find` `Disjoint Set Union` `Graph` `Connectivity` `DFS` `BFS`