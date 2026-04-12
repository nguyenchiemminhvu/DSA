## Problem

https://leetcode.com/problems/find-the-degree-of-each-vertex/description/

Given a 2D integer array `matrix` of size n × n representing the adjacency matrix of an undirected graph with n vertices labeled from 0 to n - 1:
- `matrix[i][j] = 1` indicates an edge between vertices i and j
- `matrix[i][j] = 0` indicates no edge between vertices i and j

The **degree** of a vertex is the number of edges connected to it.

**Task:** Return an integer array `ans` of size n where `ans[i]` represents the degree of vertex i.

### Examples

**Example 1:**
- Input: `matrix = [[0,1,1],[1,0,1],[1,1,0]]`
- Output: `[2,2,2]`
- Explanation: Vertex 0 connects to 1 and 2. Vertex 1 connects to 0 and 2. Vertex 2 connects to 0 and 1.

**Example 2:**
- Input: `matrix = [[0,1,0],[1,0,0],[0,0,0]]`
- Output: `[1,1,0]`
- Explanation: Vertex 0 connects to 1. Vertex 1 connects to 0. Vertex 2 has no connections.

**Example 3:**
- Input: `matrix = [[0]]`
- Output: `[0]`
- Explanation: Single vertex with no edges.

### Constraints
- 1 ≤ n = matrix.length = matrix[i].length ≤ 100
- matrix[i][i] = 0 (no self-loops)
- matrix[i][j] ∈ {0, 1}
- matrix[i][j] = matrix[j][i] (undirected graph)

## Observations

1. **Symmetric adjacency matrix:** Since the graph is undirected, `matrix[i][j] = matrix[j][i]`. This is important for avoiding double-counting.

2. **Degree calculation:** For each vertex i, we need to count all edges connected to it. In the adjacency matrix, this is the count of 1s in row i (or column i, since it's symmetric).

3. **Efficiency opportunity:** We can iterate only through the upper triangle of the matrix (i > j) or lower triangle (i < j) and count each edge once. When we find an edge between i and j, we increment both vertices' degrees.

4. **Time complexity:** We must examine every element to find all edges, so O(n²) is optimal.

5. **Space complexity:** O(n) for the output array (not counting it as extra space), O(1) additional space.

## Solution

```python
class Solution:
    def findDegrees(self, mat: list[list[int]]) -> list[int]:
        n = len(mat)
        deg = [0] * n
        
        # Only iterate through upper triangle (i < j)
        # to avoid counting each edge twice
        for i in range(n):
            for j in range(i + 1, n):
                if mat[i][j]:
                    deg[i] += 1
                    deg[j] += 1
        
        return deg
```

### Explanation

1. **Initialize:** Create a `deg` array of size n initialized to 0, which will store the degree of each vertex.

2. **Efficient iteration:** Use nested loops where the inner loop starts at `i + 1`. This ensures we only traverse the upper triangle of the adjacency matrix once, avoiding double-counting edges (since the matrix is symmetric).

3. **Count edges:** For each pair (i, j) where i < j:
   - If `mat[i][j] == 1`, there's an edge between vertices i and j
   - Increment both `deg[i]` and `deg[j]` because both vertices have their degree increased by this single edge

4. **Return result:** Return the completed `deg` array containing all degrees.

### Example Walkthrough

For `matrix = [[0,1,1],[1,0,1],[1,1,0]]`:
- i=0, j=1: mat[0][1]=1 → deg[0]++, deg[1]++ → deg=[1,1,0]
- i=0, j=2: mat[0][2]=1 → deg[0]++, deg[2]++ → deg=[2,1,1]
- i=1, j=2: mat[1][2]=1 → deg[1]++, deg[2]++ → deg=[2,2,2]
- Result: [2,2,2] ✓

### Complexity Analysis
- **Time:** O(n²) - must check each pair of vertices
- **Space:** O(1) - only using the output array

# Tags
- Graph Theory
- Matrix
- Counting

