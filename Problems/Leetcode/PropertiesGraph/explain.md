## Problem

https://leetcode.com/problems/properties-graph/description/

Given a 2D integer array `properties` of dimensions `n x m` and an integer `k`, define `intersect(a, b)` as the number of **distinct** integers common to both arrays `a` and `b`. Build an undirected graph where node `i` connects to node `j` if `intersect(properties[i], properties[j]) >= k`. Return the number of **connected components** in the resulting graph.

---

## Observations

- `intersect(a, b)` counts **distinct** common values — duplicates within a single row do not contribute extra. So `[1,1]` and `[1,1]` share only 1 distinct value.
- The graph is undirected: if `i` connects to `j`, `j` connects to `i`.
- With `n <= 100`, the number of edges is at most $\binom{100}{2} = 4950$, so an $O(n^2 \cdot m)$ approach is efficient enough.
- To compute the intersection of two rows efficiently, convert each row to a `std::set` (or `unordered_set`) and count common elements. Since `m <= 100` and values are in `[1, 100]`, a bitset or boolean array of size 101 works well.
- Finding connected components in an undirected graph is a classic Union-Find (Disjoint Set Union) or BFS/DFS problem.

---

## Approach

1. **Preprocess**: Convert each row `properties[i]` into a set of distinct integers.
2. **Build edges**: For every pair `(i, j)` with `i < j`, compute `|set[i] ∩ set[j]|`. If the count `>= k`, union nodes `i` and `j` in a DSU structure.
3. **Count components**: After processing all pairs, count the number of distinct roots in the DSU — that is the answer.

**Complexity**:
- Time: $O(n^2 \cdot m)$ — $n^2$ pairs, each intersection check is $O(m)$.
- Space: $O(n \cdot m)$ for the sets.
