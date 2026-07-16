## Problem

https://leetcode.com/problems/course-schedule-iv/description/

Given `numCourses` courses labeled `0` to `numCourses - 1` and a list of direct prerequisites `[a, b]` (meaning course `a` must be taken before course `b`), answer multiple queries of the form: **"Is course `u` a (direct or indirect) prerequisite of course `v`?"**

---

## Observations

- Prerequisites are **transitive**: if `a → b` and `b → c`, then `a` is also a prerequisite of `c`.
- The prerequisite graph is a **DAG** (no cycles guaranteed by constraints).
- `numCourses <= 100`, so an $O(n^2)$ or even $O(n^3)$ precomputation is perfectly acceptable.
- There can be up to $10^4$ queries, so answering each query from scratch with a plain DFS would be too slow. We need either **memoization** or a **precomputed reachability matrix**.

---

## Solution Explanation

### Approach: DFS with Memoization (`lru_cache`)

Build a directed graph from the prerequisites. For each query `(u, v)`, run a DFS from `u` trying to reach `v`. Because the same `(cur, target)` pair can be asked many times across different queries, results are cached with `@lru_cache`.

```python
class Solution:
    def checkIfPrerequisite(self, n: int, pre: List[List[int]], queries: List[List[int]]) -> List[bool]:
        reachable = [[False] * n for _ in range(n)]
        for i in range(n):
            reachable[i][i] = True
        
        graph = defaultdict(list)
        for u, v in pre:
            graph[u].append(v)
        
        from functools import lru_cache
        @lru_cache(None)
        def dfs(cur: int, target: int) -> bool:
            if cur == target:
                return True
            for adj in graph[cur]:
                if dfs(adj, target):
                    return True
            return False
        
        res = []
        for u, v in queries:
            res.append(dfs(u, v))
        return res
```

**Step-by-step walkthrough (Example 3):**
- `n=3`, `pre=[[1,2],[1,0],[2,0]]`, `queries=[[1,0],[1,2]]`
- Graph: `1 → [2, 0]`, `2 → [0]`
- Query `(1, 0)`: DFS from 1 → visits neighbor 2 → visits neighbor 0 → found! → `True`
- Query `(1, 2)`: DFS from 1 → visits neighbor 2 → found! → `True`
- Output: `[true, true]` ✓

**Why `lru_cache` helps:**  
The pair `(cur, target)` has at most $n^2 = 100^2 = 10000$ unique states. Once a state is computed, every future query reuses it in $O(1)$.

---

### Alternative: Floyd-Warshall (Transitive Closure)

A cleaner precomputation approach. Build an $n \times n$ boolean reachability matrix and propagate reachability through every intermediate node `k`:

```python
class Solution:
    def checkIfPrerequisite(self, n: int, pre: List[List[int]], queries: List[List[int]]) -> List[bool]:
        reach = [[False] * n for _ in range(n)]
        
        for u, v in pre:
            reach[u][v] = True
        
        # For every intermediate node k, propagate reachability
        for k in range(n):
            for i in range(n):
                for j in range(n):
                    if reach[i][k] and reach[k][j]:
                        reach[i][j] = True
        
        return [reach[u][v] for u, v in queries]
```

After the triple loop, `reach[i][j] == True` means course `i` can reach course `j` through any path. Each query is then answered in $O(1)$.

**Complexity:**
| Approach | Time | Space |
|---|---|---|
| DFS + memoization | $O(n^2 + Q)$ amortized | $O(n^2 + n + E)$ |
| Floyd-Warshall | $O(n^3 + Q)$ | $O(n^2)$ |

With $n \leq 100$ and $Q \leq 10^4$, both approaches are efficient. Floyd-Warshall is simpler to reason about; DFS with memoization is more general.
