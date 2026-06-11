## Problem

https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-i/description/

There is an undirected tree with `n` nodes labeled from `1` to `n`, rooted at node `1`. The tree is given as a 2D integer array `edges` of length `n - 1`, where `edges[i] = [ui, vi]` indicates an edge between nodes `ui` and `vi`.

Initially, all edges have a weight of `0`. You must assign each edge a weight of either `1` or `2`.

The **cost** of a path between any two nodes `u` and `v` is the total weight of all edges in that path.

Select **any one node** `x` at the **maximum depth**. Return the number of ways to assign edge weights in the path from node `1` to `x` such that its total cost is **odd**.

Since the answer may be large, return it **modulo** `10^9 + 7`.

> Note: Ignore all edges **not** in the path from node `1` to `x`.

**Example 1:**
```
Input: edges = [[1,2]]
Output: 1
Explanation:
The path from Node 1 to Node 2 has one edge (1 → 2).
Assigning weight 1 makes the cost odd; weight 2 makes it even. Answer: 1.
```

**Example 2:**
```
Input: edges = [[1,2],[1,3],[3,4],[3,5]]
Output: 2
Explanation:
Maximum depth is 2, with nodes 4 and 5. Either can be chosen.
Path from Node 1 to Node 4: two edges (1 → 3 and 3 → 4).
Assignments (1,2) or (2,1) give an odd cost. Answer: 2.
```

**Constraints:**
- `2 <= n <= 10^5`
- `edges.length == n - 1`
- `edges[i] = [ui, vi]` with `1 <= ui, vi <= n`
- `edges` represents a valid tree.

## Observations

1. **Only the path to the deepest node matters.** All edges outside this path are explicitly ignored. This reduces the problem to: given a sequence of `depth` edges, count assignments of `{1, 2}` to each edge such that the total sum is odd.

2. **All maximum-depth nodes are equivalent.** The problem says "select any one node at maximum depth." Because the tree is rooted and depth is measured from node `1`, every node at the same depth has a path of the same length from the root. It doesn't matter which one we pick — the number of edges on the path is always `depth`.

3. **Parity tracking is all we need.** We don't care about the exact total — only whether it is odd or even. Weights `1` and `2` have different parity effects:
   - Adding weight `1` (odd) **flips** the parity of the running sum.
   - Adding weight `2` (even) **preserves** the parity of the running sum.

4. **By symmetry, exactly half of all assignments give an odd sum.** For `depth` edges, there are `2^depth` total assignments. Swapping any single edge's weight `1 ↔ 2` flips the total parity, creating a perfect pairing between odd-sum and even-sum assignments. Therefore the answer is `2^(depth - 1)`.

5. **BFS finds the maximum depth.** A level-by-level BFS from node `1` counts how many levels deep the tree goes. The final level index equals the number of edges on the longest root-to-leaf path.

6. **The DP mirrors the combinatorial argument.** The memoized function `F(i, odd)` counts the number of valid complete assignments for the remaining edges from index `i` onward, given that the parity of the partial sum so far is `odd`. The two recursive calls correspond to choosing weight `1` (flip parity) or weight `2` (keep parity). This naturally evaluates to `2^(depth - 1)`.

## Solution

**Step 1 — Build the adjacency list** from the edge list so the tree can be traversed.

**Step 2 — BFS from node 1** to find the maximum depth (= number of edges on the longest root-to-leaf path).

```
depth = 0  →  only the root exists, so 0 edges on any path
depth = 1  →  one edge (e.g., [[1,2]])
depth = 2  →  two edges (e.g., path 1 → 3 → 4)
```

**Step 3 — Count valid assignments with memoized DP.**

Define `F(i, odd)`:
- `i` = index of the current edge (0-indexed, ranging from `0` to `depth - 1`)
- `odd` = whether the partial sum is currently odd (`True`) or even (`False`)
- Returns the number of ways to complete the assignment of the remaining edges so that the final sum is odd.

Recurrence:
```
F(i, odd) = F(i+1, not odd)   # assign weight 1 → flips parity
           + F(i+1, odd)      # assign weight 2 → keeps parity
```

Base case:
```
F(depth, odd) = 1 if odd else 0
```

Call `F(0, False)` (start at edge 0 with an even partial sum of 0).

**Trace for depth = 2:**
```
F(0, False) = F(1, True) + F(1, False)
F(1, True)  = F(2, False) + F(2, True)  = 0 + 1 = 1
F(1, False) = F(2, True)  + F(2, False) = 1 + 0 = 1
F(0, False) = 1 + 1 = 2  ✓
```

**Closed-form result:** `F(0, False) = 2^(depth - 1) mod (10^9 + 7)`

**Time Complexity:** O(n) for BFS + O(depth) for DP (at most O(n) unique states, each computed once).  
**Space Complexity:** O(n) for the adjacency list, visited set, and memoization table.

# Tags

`Tree`, `BFS`, `Dynamic Programming`, `Memoization`, `Recursion`, `Math`, `Parity`
