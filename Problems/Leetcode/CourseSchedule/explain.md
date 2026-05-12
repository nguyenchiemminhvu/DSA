## Problem

https://leetcode.com/problems/course-schedule/description/

There are `numCourses` courses labeled `0` to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [ai, bi]` means you must take course `bi` before course `ai`.

Return `true` if you can finish all courses, otherwise return `false`.

**Example 1:**
```
Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
```
**Example 2:**
```
Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: Course 1 requires course 0, and course 0 requires course 1 — a cycle, so impossible.
```

**Constraints:**
- `1 <= numCourses <= 2000`
- `0 <= prerequisites.length <= 5000`
- `0 <= ai, bi < numCourses`
- All prerequisite pairs are unique.

## Observations

- Model the courses and prerequisites as a **directed graph**: an edge `b → a` means "take `b` before `a`."
- If you can finish all courses, there must exist a valid ordering — i.e., the graph must be a **DAG (Directed Acyclic Graph)**.
- The problem reduces to: **does the directed graph contain a cycle?**
- A cycle means some course eventually depends on itself, making it impossible to start.
- To detect a cycle with DFS, we need to distinguish two states for each node:
  - **Visited but finished** — fully explored, no cycle found through this node. Safe to skip.
  - **Visited and currently in the recursion stack** — we are currently exploring a path through this node. Reaching it again means we found a cycle.
- A plain `visited` set is not enough: revisiting a node that was already fully explored (from a different path) is fine. Only revisiting a node that is **still on the current DFS path** indicates a cycle.

## Solution

```python
class Solution:
    def canFinish(self, n: int, pre: List[List[int]]) -> bool:
        # Build adjacency list: graph[b] contains all courses that require b
        graph = [[] for i in range(n)]
        for c, p in pre:
            graph[p].append(c)

        visited = set()   # all nodes fully processed (no cycle found through them)
        recur_st = set()  # nodes on the current DFS path

        def has_cycle(cur: int) -> bool:
            visited.add(cur)
            recur_st.add(cur)       # mark as part of current path

            for adj in graph[cur]:
                if adj not in visited:
                    if has_cycle(adj):  # recurse into unvisited neighbor
                        return True
                else:
                    if adj in recur_st:  # visited AND still on current path → cycle
                        return True

            recur_st.remove(cur)    # backtrack: done with this node
            return False

        for i in range(n):
            if i not in visited:    # only start DFS from unvisited nodes
                if has_cycle(i):
                    return False    # cycle found, cannot finish all courses
        return True
```

**Step-by-step walkthrough (Example 2: `n=2`, `prerequisites=[[1,0],[0,1]]`):**

1. Build graph: `graph[0] = [1]`, `graph[1] = [0]`
2. Start DFS from node `0`: `visited={0}`, `recur_st={0}`
3. Explore neighbor `1`: `visited={0,1}`, `recur_st={0,1}`
4. Explore neighbor `0`: already in `visited` **and** in `recur_st` → cycle detected → return `False`

**Complexity:**
- Time: $O(V + E)$ where $V$ = `numCourses`, $E$ = `prerequisites.length`
- Space: $O(V + E)$ for the graph, plus $O(V)$ for the visited/recursion sets and call stack

# Tags

`Graph` `DFS` `Cycle Detection` `Topological Sort`

