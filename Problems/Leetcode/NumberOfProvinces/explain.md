## Problem

https://leetcode.com/problems/number-of-provinces/description

Given an `n x n` matrix `isConnected` where `isConnected[i][j] = 1` indicates that city `i` and city `j` are directly connected, and `isConnected[i][j] = 0` indicates they are not directly connected:

- A **province** is a group of directly or indirectly connected cities
- Cities can be connected directly (immediate connection) or indirectly (through other cities)
- Return the total number of provinces

**Constraints:**
- `1 <= n <= 200`
- `n == isConnected.length == isConnected[i].length`
- `isConnected[i][i] == 1` (a city is always connected to itself)
- `isConnected[i][j] == isConnected[j][i]` (the graph is symmetric)

**Examples:**

Example 1:
```
Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2
Explanation: Cities 0 and 1 form one province. City 2 forms another province.
```

Example 2:
```
Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
Explanation: Each city is isolated, forming 3 separate provinces.
```

## Observations

1. **Graph Problem**: The connectivity matrix represents an undirected graph where cities are nodes and connections are edges
2. **Connected Components**: Finding provinces is equivalent to counting connected components in an undirected graph
3. **Traversal Strategy**: We need to visit all cities and group them into connected components
4. **No Duplicate Counting**: Once a city is visited as part of a province, we shouldn't count it again
5. **Symmetric Matrix**: Since `isConnected[i][j] == isConnected[j][i]`, we only need to check one direction
6. **Self-Loop**: Every city has `isConnected[i][i] == 1`, which doesn't affect our counting

## Solution

### Approach: Depth-First Search (DFS)

**Algorithm:**
1. Initialize a `visited` set to track cities that have been assigned to a province
2. Iterate through each city from 0 to n-1:
   - If the city hasn't been visited, start a DFS from that city
   - During DFS, mark all directly and indirectly connected cities as visited
   - Increment the province count
3. Return the total province count

**Why DFS works:**
- Starting from an unvisited city, DFS will explore and mark all cities in the same province as visited
- When we move to the next unvisited city, we're guaranteed to be in a different province
- The number of times we start a DFS is exactly the number of provinces

**Time Complexity:** $O(n^2)$
- We visit each city once: $O(n)$
- For each city, we check all other cities: $O(n)$
- Total: $O(n^2)$

**Space Complexity:** $O(n)$
- `visited` set: $O(n)$
- Recursion stack in worst case: $O(n)$

### Code Implementation

```python
class Solution:
    def findCircleNum(self, graph: List[List[int]]) -> int:
        n = len(graph)
        count = 0
        visited = set()

        def dfs(cur: int):
            # Explore all cities connected to the current city
            for u in range(n):
                if u not in visited and graph[cur][u]:
                    visited.add(u)
                    dfs(u)

        # Start DFS from each unvisited city
        for i in range(n):
            if i not in visited:
                visited.add(i)
                dfs(i)
                count += 1
        return count
```

### How it Works (Example 1)

Input: `[[1,1,0],[1,1,0],[0,0,1]]`

**Step-by-step execution:**

| Step | Current | Visited | Action | Count |
|------|---------|---------|--------|-------|
| 1 | 0 | {} | 0 not visited, add 0, DFS(0) | 0 |
| 2 | 0→1 | {0,1} | From 0, find 1 is connected, add 1, DFS(1) | 0 |
| 3 | 1→0 | {0,1} | From 1, check 0 (already visited), check 1 (already visited) | 0 |
| 4 | Back | {0,1} | DFS completes, increment count | 1 |
| 5 | 1 | {0,1} | 1 already visited, skip | 1 |
| 6 | 2 | {0,1} | 2 not visited, add 2, DFS(2) | 1 |
| 7 | 2→0,1,2 | {0,1,2} | From 2, no new connections, DFS completes | 1 |
| 8 | End | {0,1,2} | All cities visited, increment count | 2 |

Result: **2 provinces** ✓

### Alternative Approaches

**Union-Find (Disjoint Set Union):**
```python
class Solution:
    def findCircleNum(self, graph: List[List[int]]) -> int:
        n = len(graph)
        parent = list(range(n))
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            px, py = find(x), find(y)
            if px != py:
                parent[px] = py
        
        for i in range(n):
            for j in range(i + 1, n):
                if graph[i][j]:
                    union(i, j)
        
        return len(set(find(i) for i in range(n)))
```
- Time: $O(n^2 \cdot \alpha(n))$ where $\alpha$ is the inverse Ackermann function (nearly constant)
- Space: $O(n)$

**BFS (Breadth-First Search):**
```python
from collections import deque

class Solution:
    def findCircleNum(self, graph: List[List[int]]) -> int:
        n = len(graph)
        visited = set()
        count = 0
        
        for i in range(n):
            if i not in visited:
                queue = deque([i])
                visited.add(i)
                while queue:
                    cur = queue.popleft()
                    for u in range(n):
                        if u not in visited and graph[cur][u]:
                            visited.add(u)
                            queue.append(u)
                count += 1
        
        return count
```

# Tags

`Graph`, `DFS`, `Connected Components`, `BFS`, `Union-Find`

