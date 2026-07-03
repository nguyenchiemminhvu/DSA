## Problem

https://leetcode.com/problems/similar-string-groups/description/

Two strings `X` and `Y` are **similar** if either:
- They are identical, **or**
- Swapping exactly two letters at distinct positions in `X` produces `Y`.

Given a list `strs` of strings where every string is an anagram of every other, find the number of **connected groups** formed by the similarity relation.

**Example 1:**
```
Input:  strs = ["tars","rats","arts","star"]
Output: 2
Groups: {"tars","rats","arts"} and {"star"}
```

**Example 2:**
```
Input:  strs = ["omv","ovm"]
Output: 1
```

**Constraints:**
- `1 <= strs.length <= 300`
- `1 <= strs[i].length <= 300`
- All words have the same length and are anagrams of each other.

---

## Observations

1. **Similarity check is cheap.**  
   Two strings of length `L` are similar iff the number of positions where they differ is exactly `0` or exactly `2`. Because all strings are anagrams, a single differing position is impossible — a mismatch at one index must be compensated somewhere else, so mismatches always come in pairs (0, 2, 4, …). Only 0 or 2 differences means similar.

2. **Similarity is not transitive, but connectivity is.**  
   `"tars"` and `"arts"` differ at 3 positions, yet they are in the same group because both are similar to `"rats"`. This screams **Union-Find** (or BFS/DFS over an implicit graph).

3. **Graph model.**  
   Treat each string as a node. Add an undirected edge between any two nodes that are similar. The answer is the number of connected components in this graph.

4. **Size of the search space.**  
   Up to 300 strings × 300 strings = 90 000 pairs. Each similarity check costs O(L) with L ≤ 300, giving O(N² · L) = O(27 000 000) operations — acceptable.

5. **Early exit in similarity check.**  
   As soon as we find more than 2 differing positions we can immediately return `false`.

---

## Approach — Union-Find

**Why Union-Find?**  
We need to count connected components efficiently. Union-Find gives near O(1) amortised union and find operations with path compression + union by rank.

**Algorithm:**

1. Initialise a Union-Find structure with `N` nodes (one per string).
2. For every pair `(i, j)` with `i < j`:
   - Count differing positions between `strs[i]` and `strs[j]`.
   - If the count is `0` or `2`, call `union(i, j)`.
3. After processing all pairs, count the number of distinct roots — that is the answer.

**Similarity check:**
```
isSimilar(X, Y):
    diff = 0
    for k in 0..len(X)-1:
        if X[k] != Y[k]:
            diff++
            if diff > 2: return false
    return diff == 0 or diff == 2
```

**Complexity:**
- Time: $O(N^2 \cdot L)$ where $N$ = number of strings, $L$ = string length.
- Space: $O(N)$ for the Union-Find arrays.
