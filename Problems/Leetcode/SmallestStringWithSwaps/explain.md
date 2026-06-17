## Problem

https://leetcode.com/problems/smallest-string-with-swaps/

You are given a string `s` and an array of index pairs `pairs`, where `pairs[i] = [a, b]` lets you swap the characters at indices `a` and `b` **any number of times**. Return the lexicographically smallest string reachable through such swaps.

### Examples:
- **Example 1**: `s = "dcab"`, `pairs = [[0,3],[1,2]]` → Output: `"bacd"`
  - Indices `{0,3}` and `{1,2}` form two independent swap groups. Sort `"da"` → `"ad"` for positions `{0,3}` and `"cb"` → `"bc"` for positions `{1,2}`.
- **Example 2**: `s = "dcab"`, `pairs = [[0,3],[1,2],[0,2]]` → Output: `"abcd"`
  - All four indices are now linked into a single group, so the whole string can be sorted.
- **Example 3**: `s = "cba"`, `pairs = [[0,1],[1,2]]` → Output: `"abc"`
  - Indices `0-1` and `1-2` are chained, so all three indices belong to one group.

### Constraints:
- `1 <= s.length <= 10^5`
- `0 <= pairs.length <= 10^5`
- `0 <= pairs[i][0], pairs[i][1] < s.length`
- `s` contains only lowercase English letters.

## Observations

1. **Swaps are transitive**: If we can swap `(a, b)` and `(b, c)`, then by chaining swaps we can place any character of `{a, b, c}` at any of those three positions. So a pair acts more like an *undirected edge* between indices than a one-shot operation.

2. **Connected components**: Treat indices as nodes and each pair as an edge. Inside one connected component, characters can be freely permuted to any arrangement (think of bubble-sort over the component's indices using adjacent swaps along the spanning tree).

3. **Greedy per component**: To minimize the string lexicographically, within each component place the smallest character at the smallest index, the next smallest at the next index, and so on. This is optimal because any other assignment for that component would put a larger character at an earlier index, increasing the string lexicographically.

4. **Components are independent**: Sorting one component never affects another, so we can process them in any order.

5. **Union-Find fits perfectly**: We only need to know which indices share a component — not the exact graph structure — so a Disjoint Set Union (DSU) is ideal and avoids building an explicit adjacency list + BFS/DFS.

## Solution

The solution uses **Disjoint Set Union (Union-Find) + sorting per component**:

### Approach:
1. **Build components with DSU**: For every pair `(a, b)`, union the two indices. After processing all pairs, indices in the same component share the same root.
2. **Group indices by root**: Walk through every index `i`, find its root, and append `(s[i], i)` into a bucket keyed by the root.
3. **Sort and rewrite each bucket**:
   - Sort the bucket by character (smallest character first).
   - Sort the indices in the bucket ascending (smallest index first).
   - Assign the *k-th smallest character* to the *k-th smallest index*.
4. **Join the modified character array** into the final string.

### Why DSU works:
- **Path compression** in `find` flattens the tree, making subsequent lookups near-constant.
- **Union by rank** keeps trees shallow, so `union` is also near-constant amortized.
- Combined, all `m` pair operations cost `O((n + m) · α(n))`, where `α` is the inverse Ackermann function (effectively constant).

### Complexity:
- **Time**: `O((n + m) · α(n) + n log n)` — DSU operations over `n` indices and `m` pairs, plus sorting characters/indices across all components (total size `n`).
- **Space**: `O(n)` for the DSU arrays, the bucket map, and the mutable character list.

### Code walkthrough:
```python
class DSU:
    def __init__(self, n: int):
        self.parent = list(range(n))
        self.rank = [1] * n

    def find(self, x):
        # Path compression: re-point x (and its ancestors) directly to the root
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        rx, ry = self.find(x), self.find(y)
        if rx == ry:
            return False
        # Union by rank: attach the shorter tree under the taller one
        if self.rank[rx] > self.rank[ry]:
            self.parent[ry] = rx
        elif self.rank[rx] < self.rank[ry]:
            self.parent[rx] = ry
        else:
            self.parent[ry] = rx
            self.rank[rx] += 1
        return True

class Solution:
    def smallestStringWithSwaps(self, s: str, pairs: List[List[int]]) -> str:
        n = len(s)
        s = list(s)                       # strings are immutable in Python; use a list

        dsu = DSU(n)
        for a, b in pairs:                # 1) Build connected components
            dsu.union(a, b)

        mp = defaultdict(list)            # 2) Group (char, index) pairs by component root
        for i in range(n):
            root = dsu.find(i)
            mp[root].append((s[i], i))

        for root, arr in mp.items():      # 3) For each component:
            arr.sort()                    #    sort characters ascending
            indices = sorted(i for _, i in arr)  # sort indices ascending
            for k in range(len(arr)):
                s[indices[k]] = arr[k][0] # place k-th smallest char at k-th smallest index

        return ''.join(s)                 # 4) Reassemble the string
```

### Walkthrough on Example 2 (`s = "dcab"`, `pairs = [[0,3],[1,2],[0,2]]`):
- After unions, indices `{0, 1, 2, 3}` collapse into a single component.
- Bucket characters: `[('d',0), ('c',1), ('a',2), ('b',3)]`.
- Sorted characters: `['a','b','c','d']`; sorted indices: `[0,1,2,3]`.
- Assign `a→0, b→1, c→2, d→3` → `"abcd"`.

# Tags
- Union-Find (Disjoint Set Union)
- Graph / Connected Components
- Sorting
- Hash Map (grouping by root)
- Greedy

