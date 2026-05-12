## Problem

https://leetcode.com/problems/course-schedule-ii/description

# Course Schedule II

## Problem

https://leetcode.com/problems/course-schedule-ii/description

There are a total of `numCourses` courses you have to take, labeled from `0` to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [ai, bi]` indicates that you must take course `bi` first if you want to take course `ai`.

**Return the ordering of courses you should take to finish all courses.** If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

### Examples

**Example 1:**
- Input: `numCourses = 2, prerequisites = [[1,0]]`
- Output: `[0,1]`
- Explanation: To take course 1 you should have finished course 0. So the correct course order is [0,1].

**Example 2:**
- Input: `numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]`
- Output: `[0,2,1,3]`
- Explanation: To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].

**Example 3:**
- Input: `numCourses = 1, prerequisites = []`
- Output: `[0]`

### Constraints

- $1 \leq \text{numCourses} \leq 2000$
- $0 \leq \text{prerequisites.length} \leq \text{numCourses} \times (\text{numCourses} - 1)$
- `prerequisites[i].length == 2`
- $0 \leq a_i, b_i < \text{numCourses}$
- $a_i \neq b_i$
- All the pairs $[a_i, b_i]$ are distinct

---

## Observations

1. **Graph Problem**: This is a classic topological sort problem. Each course is a node, and each prerequisite relationship is a directed edge from the prerequisite to the course.

2. **Cycle Detection**: If there's a cycle in the graph, it's impossible to complete all courses (circular dependency). We need to detect this during traversal.

3. **Topological Ordering**: A valid course ordering is one where for every prerequisite relationship [a, b], course b appears before course a in the result.

4. **DFS with Recursion Stack**: We can use DFS with a recursion stack to detect cycles:
   - A cycle exists if we encounter a node that's currently in the recursion stack (back edge).
   - If no cycle is found, we can build a valid topological order.

5. **Post-order Addition**: In DFS, we add a node to the result after visiting all its descendants. This ensures that dependencies are satisfied before a node is added.

6. **Reverse for Correct Order**: Since we add nodes in post-order (during backtracking), we need to reverse the result to get the topological ordering.

---

## Solution

### Approach: DFS-based Topological Sort with Cycle Detection

**Algorithm:**
1. Build an adjacency list graph where an edge from `b` to `a` means "course b is a prerequisite for course a".
2. Use DFS to traverse the graph while maintaining:
   - `visited`: Set of all nodes we've fully processed
   - `recur_st`: Set of nodes in the current recursion stack (to detect cycles)
3. For each unvisited node, start a DFS:
   - Mark it as visited and add it to the recursion stack
   - Recursively visit all unvisited neighbors
   - If we encounter a node in the recursion stack, we found a cycle → return False
   - After visiting all neighbors, remove from recursion stack and add to result
4. Reverse the result to get the correct topological order
5. Return empty array if cycle detected, otherwise return the topological order

### Code Explanation

```python
class Solution:
    def findOrder(self, n: int, pre: List[List[int]]) -> List[int]:
        # Step 1: Build adjacency list
        # graph[i] contains all courses that depend on course i
        graph = [[] for i in range(n)]
        for c, p in pre:
            graph[p].append(c)  # p is prerequisite for c
        
        visited = set()        # Nodes fully processed
        recur_st = set()       # Nodes in current recursion stack
        
        def dfs(cur: int, topo: List[int]) -> bool:
            # Mark as visited and add to recursion stack
            visited.add(cur)
            recur_st.add(cur)
            
            # Visit all dependent courses
            for adj in graph[cur]:
                if adj not in visited:
                    # Recursively process unvisited dependent
                    if not dfs(adj, topo):
                        return False  # Cycle detected in recursion
                
                # Check if adjacent is in current recursion stack
                # (indicates a back edge - cycle exists)
                if adj in recur_st:
                    return False
            
            # Backtrack: remove from recursion stack
            recur_st.remove(cur)
            
            # Add to result after processing all dependencies
            topo.append(cur)
            return True
        
        def build_topo() -> List[int]:
            topo = []
            # Start DFS from each unvisited node
            for i in range(n):
                if i not in visited:
                    if not dfs(i, topo):
                        return []  # Cycle detected
            
            # Reverse to get correct topological order
            topo.reverse()
            return topo
        
        return build_topo()
```

### Complexity Analysis

- **Time Complexity**: $O(V + E)$ where $V$ is the number of courses and $E$ is the number of prerequisites. We visit each course once and traverse each edge once.
- **Space Complexity**: $O(V + E)$ for the adjacency list and recursion stack in the worst case.

### Key Points

1. **Cycle Detection**: The recursion stack technique detects cycles by checking if we revisit a node that's already in the current recursion path.
2. **Post-order Traversal**: Nodes are added to the result after all their dependencies are processed, ensuring correct ordering.
3. **Why Reverse**: DFS processes nodes in post-order (children first), so the last processed node is the one with no dependencies. Reversing gives us the correct topological order.

---

## Tags

#topological-sort #graph #cycle-detection #dfs #medium

## Observations

## Solution

# Tags

