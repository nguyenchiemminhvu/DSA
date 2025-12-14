## Problem

https://leetcode.com/problems/all-paths-from-source-to-target/description/

```
Given a directed acyclic graph (DAG) of n nodes labeled from 0 to n - 1, 
find all possible paths from node 0 to node n - 1 and return them in any order.

The graph is given as follows: graph[i] is a list of all nodes you can visit 
from node i (i.e., there is a directed edge from node i to node graph[i][j]).

Example 1:
Input: graph = [[1,2],[3],[3],[]]
Output: [[0,1,3],[0,2,3]]
Explanation: There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.

Example 2:
Input: graph = [[4,3,1],[3,2,4],[3],[4],[]]
Output: [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]

Constraints:
- n == graph.length
- 2 <= n <= 15
- 0 <= graph[i][j] < n
- graph[i][j] != i (i.e., there will be no self-loops)
- All the elements of graph[i] are unique
- The input graph is guaranteed to be a DAG
```

## Observations

1. **Graph Structure**: The graph is a directed acyclic graph (DAG), which guarantees:
   - No cycles exist, so we won't get stuck in infinite loops
   - Every path will eventually terminate
   - We don't need to worry about revisiting nodes creating cycles

2. **Path Finding**: We need to find ALL paths from node 0 to node n-1, not just one path or the shortest path.

3. **Small Input Size**: The constraint `n <= 15` indicates that the graph is small, making a backtracking/DFS approach feasible even though it explores all possibilities.

4. **Backtracking Approach**: Since we need all paths, a depth-first search (DFS) with backtracking is ideal:
   - Explore each path from node 0
   - When we reach node n-1, save the current path
   - Backtrack to explore other possible paths

5. **State Management**: We need to track:
   - Current path being explored
   - Visited nodes (to avoid revisiting in the current path)
   - All complete paths found

## Solution

### Approach: DFS with Backtracking

**Algorithm:**

1. **Initialization:**
   - Create a result list to store all valid paths
   - Create a path list to track the current path being explored
   - Create a visited array to mark visited nodes in the current path
   - Mark node 0 as visited (starting point)

2. **DFS Traversal:**
   - Start DFS from node 0
   - For each node, check if it's the destination (n-1)
     - If yes, add the complete path (including node 0) to results
     - If no, explore all adjacent unvisited nodes
   
3. **Backtracking:**
   - Before exploring an adjacent node:
     - Mark it as visited
     - Add it to the current path
   - After exploring (recursion returns):
     - Remove it from the current path
     - Mark it as unvisited
   
   This allows us to reuse the node in other paths.

**Code Walkthrough:**

```python
class Solution:
    def allPathsSourceTarget(self, graph: List[List[int]]) -> List[List[int]]:
        n = len(graph)
        res = []              # Store all valid paths
        path = []             # Current path (excluding node 0)
        visited = [False] * n # Track visited nodes in current path
        
        def dfs(cur: int) -> None:
            # Base case: reached destination
            if cur == n - 1:
                res.append([0] + path[:])  # Add complete path with node 0
                return
            
            # Explore all adjacent nodes
            for adj in graph[cur]:
                if not visited[adj]:
                    # Choose: mark as visited and add to path
                    visited[adj] = True
                    path.append(adj)
                    
                    # Explore
                    dfs(adj)
                    
                    # Unchoose: backtrack
                    path.pop()
                    visited[adj] = False
        
        visited[0] = True  # Start from node 0
        dfs(0)
        return res
```

**Key Points:**

1. **Path Representation**: The `path` list stores nodes from the current node onwards (excluding 0), which is why we prepend 0 when saving: `[0] + path[:]`

2. **Path Copy**: We use `path[:]` to create a copy of the path list, ensuring each result has its own list instance.

3. **Visited Array**: Although the graph is a DAG (no cycles), the visited array prevents revisiting nodes within the same path exploration. This is important because a node can appear in multiple different paths but not multiple times in the same path.

4. **Backtracking Pattern**: The classic "choose-explore-unchoose" pattern:
   ```python
   visited[adj] = True    # Choose
   path.append(adj)
   dfs(adj)               # Explore
   path.pop()             # Unchoose
   visited[adj] = False
   ```

**Complexity Analysis:**

- **Time Complexity**: $O(2^n \cdot n)$
  - In the worst case (complete graph), we might have $2^n$ paths
  - Each path can have up to $n$ nodes
  - Creating each path copy takes $O(n)$ time
  
- **Space Complexity**: $O(n)$
  - Recursion depth: $O(n)$ (maximum path length)
  - Path storage: $O(n)$
  - Visited array: $O(n)$
  - Note: The output space is not counted in space complexity analysis

**Alternative Approach:**

Since the graph is a DAG, we could actually omit the visited array and the solution would still work correctly (no cycles to worry about). However, using the visited array is a good practice and may prevent redundant exploration in some graph structures.

# Tags

`Graph` `Depth-First Search` `Backtracking` `Directed Acyclic Graph` `Path Finding`

