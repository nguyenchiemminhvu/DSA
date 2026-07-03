## Problem

https://leetcode.com/problems/lexicographically-smallest-equivalent-string/

You are given two strings `s1` and `s2` of the same length, and a string `baseStr`. Characters
`s1[i]` and `s2[i]` are **equivalent**. Equivalency follows the standard rules of an equivalence
relation:

- **Reflexivity**: `'a' == 'a'`
- **Symmetry**: `'a' == 'b'` implies `'b' == 'a'`
- **Transitivity**: `'a' == 'b'` and `'b' == 'c'` implies `'a' == 'c'`

Return the **lexicographically smallest** equivalent string of `baseStr` using the equivalency
information from `s1` and `s2`.

### Examples

- **Example 1**:
  - Input: `s1 = "parker"`, `s2 = "morris"`, `baseStr = "parser"`
  - Output: `"makkek"`
  - Explanation: Equivalency groups are `[m,p]`, `[a,o]`, `[k,r,s]`, `[e,i]`.
    Each character in `baseStr` is replaced by the smallest in its group.

- **Example 2**:
  - Input: `s1 = "hello"`, `s2 = "world"`, `baseStr = "hold"`
  - Output: `"hdld"`
  - Explanation: Groups are `[h,w]`, `[d,e,o]`, `[l,r]`.
    `'o'` → `'d'`, everything else is already minimal.

- **Example 3**:
  - Input: `s1 = "leetcode"`, `s2 = "programs"`, `baseStr = "sourcecode"`
  - Output: `"aauaaaaada"`
  - Explanation: Groups are `[a,o,e,r,s,c]`, `[l,p]`, `[g,t]`, `[d,m]`.
    Most letters in `baseStr` fall into the big group whose minimum is `'a'`.

### Constraints

- `1 <= s1.length, s2.length, baseStr.length <= 1000`
- `s1.length == s2.length`
- `s1`, `s2`, and `baseStr` consist of lowercase English letters only.

---

## Observations

1. **Characters are the nodes, not indices**: Unlike typical Union-Find problems where
   we union array *indices*, here the nodes are the **26 lowercase letters** themselves.
   The DSU has a fixed size of exactly 26, regardless of how long the input strings are.

2. **Each pair `(s1[i], s2[i])` is a graph edge**: Treating letters as nodes and each
   equivalency pair as an undirected edge, the equivalence classes are exactly the
   **connected components** of this character graph.

3. **Transitivity = connected components**: The problem explicitly states transitivity,
   which means we are dealing with a proper equivalence relation. All characters reachable
   from each other through any chain of equivalencies form one equivalence class. This is
   precisely what a connected component captures.

4. **The answer per character = minimum of its component**: To minimize `baseStr`
   lexicographically, every character should become the **smallest character in its
   equivalence class**. This is because the smallest character is the best possible
   replacement — any other member of the class is larger and would make the string
   lexicographically larger.

5. **Two ways to track the minimum per component**:
   - **Union by minimum character**: Modify the union rule so the smaller character's
     root always becomes the combined root. Then `find(c)` directly returns the smallest
     character index in the component.
   - **Separate tracking with a heap**: Use standard DSU (union by rank) and maintain a
     min-heap per root to track the minimum character. Query the heap's top after all
     unions are done.

6. **Bounded problem → near-constant cost**: Since there are only 26 nodes, every DSU
   operation is bounded by `α(26) ≤ 4`, which is effectively constant. The dominant
   cost is the linear scan of `s1`/`s2` and `baseStr`.

---

## Approach — Union-Find (Disjoint Set Union) on 26 Characters

### Step 1 — Initialize DSU over 26 letters

Create a DSU with 26 slots (`0` = `'a'`, `1` = `'b'`, …, `25` = `'z'`).
Initially every letter is its own root (no equivalencies yet).

```
parent = [0, 1, 2, ..., 25]
```

### Step 2 — Union all equivalency pairs

For each index `i`, union `s1[i]` with `s2[i]`.

```
s1 = "parker", s2 = "morris"
  i=0: union('p', 'm')  → p(15) ↔ m(12)
  i=1: union('a', 'o')  → a(0)  ↔ o(14)
  i=2: union('r', 'r')  → no-op (same node)
  i=3: union('k', 'r')  → k(10) ↔ r(17)
  i=4: union('e', 'i')  → e(4)  ↔ i(8)
  i=5: union('r', 's')  → r(17) ↔ s(18)  [now k, r, s are all connected]
```

After all unions, the connected components (equivalence classes) are:
`{m, p}`, `{a, o}`, `{k, r, s}`, `{e, i}`, and all other letters are singletons.

### Step 3 — Determine the minimum character per component

Scan all 26 characters and group them by their DSU root. The minimum character in each
group is its smallest index (since `'a'` = 0, `'b'` = 1, etc., the smallest index = the
lexicographically smallest character).

```
groups = {
  root_of_m: {'m', 'p'} → min = 'm'
  root_of_a: {'a', 'o'} → min = 'a'
  root_of_k: {'k', 'r', 's'} → min = 'k'
  root_of_e: {'e', 'i'} → min = 'e'
  ...
}
```

### Step 4 — Build the result string

For each character `c` in `baseStr`:
1. Find its DSU root.
2. Look up the minimum character for that root.
3. Append it to the result.

```
baseStr = "parser"
  'p' → component {m, p} → 'm'
  'a' → component {a, o} → 'a'
  'r' → component {k, r, s} → 'k'
  's' → component {k, r, s} → 'k'
  'e' → component {e, i} → 'e'
  'r' → component {k, r, s} → 'k'
Result: "makkek"  ✓
```

---

## Solution

The solution uses **DSU with union by rank** plus a **min-heap per component** to track
the lexicographically smallest character in each equivalency group.

```python
from collections import defaultdict
import heapq

class DSU:
    def __init__(self, size):
        self.parent = list(range(size))
        self.rank = [0] * size

    def find(self, i):
        if self.parent[i] != i:
            self.parent[i] = self.find(self.parent[i])  # path compression
        return self.parent[i]

    def union(self, i, j):
        root_i = self.find(i)
        root_j = self.find(j)
        if root_i != root_j:
            # Union by rank: keep the tree shallow
            if self.rank[root_i] > self.rank[root_j]:
                self.parent[root_j] = root_i
            elif self.rank[root_i] < self.rank[root_j]:
                self.parent[root_i] = root_j
            else:
                self.parent[root_j] = root_i
                self.rank[root_i] += 1

class Solution:
    def smallestEquivalentString(self, s1: str, s2: str, base: str) -> str:
        dsu = DSU(26)

        # Step 2: union all equivalency pairs
        for i in range(len(s1)):
            i1 = ord(s1[i]) - ord('a')
            i2 = ord(s2[i]) - ord('a')
            dsu.union(i1, i2)

        # Step 3: build a min-heap per component root
        groups = {}
        for i in range(26):
            root = dsu.find(i)
            if root not in groups:
                groups[root] = []
            heapq.heappush(groups[root], i)  # smallest index = smallest letter

        # Step 4: replace each character in baseStr with its component's minimum
        res = []
        for c in base:
            i = ord(c) - ord('a')
            root = dsu.find(i)
            min_lex = groups[root][0]       # heap top = minimum character index
            res.append(chr(ord('a') + min_lex))

        return "".join(res)
```

### Alternative: Union by Minimum Character

Instead of using a separate heap, we can change the union strategy so the **smaller
character always becomes the root**. Then `find(c)` directly returns the minimum character
index in the component — no extra data structure needed.

```python
def union(self, i, j):
    root_i = self.find(i)
    root_j = self.find(j)
    if root_i != root_j:
        # Always make the smaller character the root
        if root_i < root_j:
            self.parent[root_j] = root_i
        else:
            self.parent[root_i] = root_j
```

With this variant, the `groups` step is replaced by a direct `find()` call:

```python
for c in base:
    i = ord(c) - ord('a')
    min_lex = dsu.find(i)   # find() returns the min character index directly
    res.append(chr(ord('a') + min_lex))
```

> **Trade-off**: Union by minimum sacrifices the tree-height guarantee of union by rank
> (the tree may become slightly taller). In practice this is irrelevant here because the
> DSU has only 26 nodes, so the depth is bounded by `log₂(26) < 5` even without any rank
> optimization.

---

## Complexity

| | Value |
|---|---|
| **Time** | $O((|s1| + |baseStr|) \cdot \alpha(26))$ ≈ $O(|s1| + |baseStr|)$ — linear in the input lengths; $\alpha(26) \le 4$ is effectively constant |
| **Space** | $O(26)$ = $O(1)$ — fixed DSU and grouping arrays over the 26-letter alphabet |

---

## Comparison to Similar Problems

| Problem | Nodes in DSU | Goal |
|---|---|---|
| **This problem** | 26 characters | Replace each char with its component's minimum |
| Smallest String With Swaps | `n` string indices | Sort characters within each component |
| Satisfiability of Equality Equations | 26 characters | Check if `!=` constraints contradict `==` components |
| Accounts Merge | Email strings → indices | Merge accounts sharing a common email |

---

## Tags

`Union-Find` `Disjoint Set Union` `Graph` `String` `Greedy`
