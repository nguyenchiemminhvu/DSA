## Problem

https://leetcode.com/problems/add-edges-to-make-degrees-of-all-nodes-even/description

Given an undirected graph of `n` nodes (labeled `1` to `n`) and a list of edges, determine whether it is possible to add **at most 2 additional edges** (no duplicates, no self-loops) so that every node in the graph has an **even degree**.

---

## Observations

**1. The Handshaking Lemma**  
The sum of all node degrees always equals `2 * |edges|`, which is always even. Therefore, the **number of odd-degree nodes is always even** (0, 2, 4, 6, …).

**2. Each added edge changes the parity of exactly 2 nodes**  
Adding an edge `(u, v)` increments the degree of both `u` and `v` by 1, flipping their parity. An odd node becomes even and vice versa.

**3. We can fix at most 4 odd-degree nodes**  
- With **0 edges added**: 0 odd-degree nodes can be fixed.  
- With **1 edge added**: exactly 2 odd-degree nodes can be fixed (connect them directly).  
- With **2 edges added**: exactly 4 odd-degree nodes can be fixed (pair them up, one edge per pair).  

So the only solvable cases are when there are **0, 2, or 4** odd-degree nodes. Any other count (e.g., 6 or more) is impossible.

**4. The 2-odd-node case has a "medium node" trick**  
If the two odd nodes `a` and `b` are **already connected**, we can't use a direct edge. Instead, find any third node `m` such that neither `(a, m)` nor `(b, m)` already exists — adding both edges makes `a` and `b` even while `m` gains and then loses parity, staying even overall.

**5. The 4-odd-node case reduces to 3 pairings**  
For four odd nodes `{a, b, c, d}`, there are exactly **3 ways** to pair them into 2 edges:
- `(a,b)` and `(c,d)`
- `(a,c)` and `(b,d)`
- `(a,d)` and `(b,c)`

We just need any one valid pairing (both edges must be new).

---

## Solution Explanation

```python
class Solution:
    def isPossible(self, n: int, edges: List[List[int]]) -> bool:
        mp = defaultdict(set)
        for u, v in edges:
            mp[u].add(v)
            mp[v].add(u)
        
        odds = [node for node in range(1, n + 1) if len(mp[node]) & 1]

        no = len(odds)
        if no == 0:
            return True
        
        if no == 2:
            a, b = odds
            if b not in mp[a]:
                return True
            for medium in range(1, n + 1):
                if medium != a and medium != b and medium not in mp[a] and medium not in mp[b]:
                    return True
            return False
        
        if no == 4:
            a, b, c, d = odds
            # (a, b) and (c, d)
            if b not in mp[a] and d not in mp[c]:
                return True

            # (a, c) and (b, d)
            if c not in mp[a] and d not in mp[b]:
                return True

            # (a, d) and (b, c)
            if d not in mp[a] and c not in mp[b]:
                return True

            return False

        return False
```

**Step 1 — Build adjacency sets**  
Use `defaultdict(set)` so that checking whether an edge `(u, v)` already exists is O(1).

**Step 2 — Collect odd-degree nodes**  
Iterate all nodes from `1` to `n` and filter those with odd degree (`len(mp[node]) & 1`).

**Step 3 — Case `no == 0`**  
All degrees are already even. Return `True` immediately.

**Step 4 — Case `no == 2`**  
Two odd nodes `a` and `b`:
- If `(a, b)` doesn't exist yet → add it directly. Both become even. ✅  
- Otherwise, search for a **medium node** `m` not adjacent to either `a` or `b`. Adding `(a, m)` and `(b, m)`:
  - `a`: odd → even ✅
  - `b`: odd → even ✅
  - `m`: even → odd → even ✅ (two edges added to it)
- If no such `m` exists → return `False`.

**Step 5 — Case `no == 4`**  
Four odd nodes `a, b, c, d`. Try all 3 pairings. If any pairing produces two edges that don't already exist in the graph, return `True`. Otherwise return `False`.

**Step 6 — Any other count**  
The final `return False` handles all other even counts (6, 8, …) that cannot be fixed with only 2 edges.

---

## Complexity

| | Value |
|---|---|
| **Time** | O(n + E) — building the adjacency map is O(E), scanning for odd nodes is O(n), all case checks are O(n) at most |
| **Space** | O(n + E) — adjacency sets |
