## Problem

https://leetcode.com/problems/evaluate-division/description

### Problem Statement

You are given an array of variable pairs `equations` and an array of real numbers `values`, where `equations[i] = [Ai, Bi]` and `values[i]` represent the equation `Ai / Bi = values[i]`. Each `Ai` or `Bi` is a string representing a single variable.

You are also given some `queries`, where `queries[j] = [Cj, Dj]` represents the j-th query asking to find the answer for `Cj / Dj = ?`.

Return the answers to all queries. If a single answer cannot be determined, return `-1.0`.

**Constraints:**
- Variables that do not occur in the equations are undefined → answer is `-1.0`
- The input is always valid with no division by zero or contradictions

**Examples:**

Example 1:
```
equations = [["a","b"],["b","c"]], values = [2.0,3.0]
queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]

Given: a/b = 2.0, b/c = 3.0
- a/c = 2.0 * 3.0 = 6.0
- b/a = 1/2.0 = 0.5
- a/e = -1.0 (e is undefined)
- a/a = 1.0 (dividing by itself)
- x/x = -1.0 (x is undefined)
```

## Observations

1. **Graph Structure**: Each equation can be represented as a **weighted bidirectional edge** in a graph:
   - For `a/b = k`, create edge: `a -> (k, b)` and `b -> (1/k, a)`
   - The weight represents the ratio value

2. **Path Traversal**: To find `c/d`, we need to find a **path from c to d** in the graph:
   - The answer is the **product of all edge weights** along the path
   - If no path exists, return `-1.0`

3. **Undefined Variables**: A variable is only defined if it appears in at least one equation. Check if both variables exist in the graph before querying.

4. **Self-division**: A variable divided by itself is always `1.0` (if it's defined).

5. **Reciprocal Relationship**: If we can compute `a/b`, we can also compute `b/a = 1/(a/b)` by reversing the path.

## Solution

### Approach: Weighted Graph + DFS

**Core Idea**: Model variable relationships as a weighted directed graph where edges represent division ratios. Use DFS to find the path from source to target and multiply the edge weights.

**Algorithm:**

1. **Build Graph**:
   - Create adjacency list where `graph[var]` stores list of `(weight, neighbor)` tuples
   - For equation `a/b = val`: add `(val, b)` to `graph[a]` and `(1/val, a)` to `graph[b]`

2. **Query Processing**:
   - If either variable not in graph → return `-1.0`
   - Otherwise, use DFS to find path from `var1` to `var2`

3. **DFS Search**:
   - Base case: if `current == target`, return `1.0` (found path)
   - Explore neighbors, multiply their results by edge weight
   - Use `visited` set to avoid cycles
   - If no path found, return `-1.0`

**Time Complexity:**
- Graph building: O(E) where E = number of equations
- Per query: O(V + E) for DFS where V = number of unique variables
- Total: O(E + Q*(V+E)) where Q = number of queries

**Space Complexity:**
- Graph storage: O(E)
- DFS call stack: O(V)
- Total: O(V + E)

### Implementation

```python
class Solution:
    def calcEquation(self, equations: List[List[str]], values: List[float], queries: List[List[str]]) -> List[float]:
        # Build weighted graph: var -> [(ratio, neighbor), ...]
        graph = {}
        for i in range(len(values)):
            var1, var2 = equations[i]
            val = values[i]
            # a/b = val means: a -> val*b and b -> (1/val)*a
            graph.setdefault(var1, []).append((val, var2))
            graph.setdefault(var2, []).append((1/val, var1))
        
        def dfs(cur: str, target: str, visited: set[str]) -> float:
            # Base case: reached target
            if cur == target:
                return 1.0
            
            visited.add(cur)
            
            # Explore all neighbors
            for next_cost, next_node in graph[cur]:
                if next_node not in visited:
                    res = dfs(next_node, target, visited)
                    # If path found in subtree, multiply edge weight
                    if res != -1.0:
                        return res * next_cost
            
            # No path found
            return -1.0
        
        res = []
        for var1, var2 in queries:
            # Both variables must be defined in equations
            if var1 not in graph or var2 not in graph:
                res.append(-1.0)
            else:
                res.append(dfs(var1, var2, set()))
        
        return res
```

### Example Walkthrough

**Example 1**: `equations = [["a","b"],["b","c"]], values = [2.0,3.0]`

**Graph**:
```
a --2.0--> b
a <-0.5-- b
b --3.0--> c
b <-0.333--> c
```

**Query: "a" / "c"**
- DFS from "a" to "c"
- Path: a → b (cost 2.0) → c (cost 3.0)
- Result: 2.0 × 3.0 = 6.0 ✓

**Query: "b" / "a"**
- DFS from "b" to "a"
- Path: b → a (cost 0.5)
- Result: 0.5 ✓

# Tags
Graph, DFS, Union-Find

