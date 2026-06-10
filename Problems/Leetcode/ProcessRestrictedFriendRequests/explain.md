## Problem

https://leetcode.com/problems/process-restricted-friend-requests/description/

Given `n` people (labeled `0` to `n-1`), a list of `restrictions` where `restrictions[i] = [x, y]` means `x` and `y` can **never** be friends (directly or indirectly), and a list of `requests` where `requests[j] = [u, v]` is a friend request — process each request in order and return a boolean array `result` where `result[j]` is `true` if the request can be granted without violating any restriction.

---

## Observations

1. **Friendship is transitive (union-find structure).** If A–B and B–C are friends, then A and C are indirectly friends. This naturally maps to a Disjoint Set Union (DSU) / Union-Find data structure where each connected component represents a group of mutual friends.

2. **A request `[u, v]` is valid if and only if merging their groups does not connect any restricted pair.** Specifically, for every restriction `[x, y]`, after a hypothetical merge of `u` and `v`, `x` and `y` must still be in different components.

3. **We don't need to actually merge — we just check roots.** Before merging `u` and `v`, find their roots `ru` and `rv`. For each restriction `[x, y]` with roots `rx` and `ry`, the merge would connect the restricted pair if:
   - `ru == rx` and `rv == ry`, **or**
   - `ru == ry` and `rv == rx`

   Because merging `ru` and `rv` would place `x` (in `ru`'s or `rv`'s group) and `y` (in the other) into the same component.

4. **Only union on valid requests.** If the request is valid, perform the union. Future requests will see the updated components.

---

## Solution Explanation

```python
class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, i):
        if self.parent[i] != i:
            self.parent[i] = self.find(self.parent[i])  # path compression
        return self.parent[i]

    def union(self, i, j):
        root_i = self.find(i)
        root_j = self.find(j)
        if root_i != root_j:
            if self.rank[root_i] < self.rank[root_j]:
                self.parent[root_i] = root_j
            elif self.rank[root_i] > self.rank[root_j]:
                self.parent[root_j] = root_i
            else:
                self.parent[root_j] = root_i
                self.rank[root_i] += 1

    def connected(self, i, j):
        return self.find(i) == self.find(j)

class Solution:
    def friendRequests(self, n, restrictions, requests):
        nr = len(requests)
        res = [False] * nr
        dsu = DSU(n)

        for i, (u, v) in enumerate(requests):
            ru, rv = dsu.find(u), dsu.find(v)
            valid = True

            for x, y in restrictions:
                rx, ry = dsu.find(x), dsu.find(y)
                # Would merging ru and rv place x and y in the same component?
                if (ru == rx and rv == ry) or (ru == ry and rv == rx):
                    valid = False
                    break

            res[i] = valid
            if valid:
                dsu.union(u, v)

        return res
```

**Step-by-step:**

- Initialize DSU with `n` nodes (each person is their own component).
- For each request `[u, v]`:
  - Find the root of `u` (`ru`) and `v` (`rv`).
  - For every restriction `[x, y]`, find `rx` and `ry`.
  - If the would-be merge connects `x`'s group to `y`'s group (i.e., `{ru,rv} == {rx,ry}` as sets), reject the request.
  - If no restriction is violated, accept and union `u` and `v`.

**Complexity:**
- Time: $O(Q \cdot R \cdot \alpha(N))$ where $Q$ = number of requests, $R$ = number of restrictions, $\alpha$ is the inverse Ackermann function (near-constant for DSU operations).
- Space: $O(N)$ for the DSU.
