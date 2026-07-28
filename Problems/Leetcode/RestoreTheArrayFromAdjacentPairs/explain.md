## Problem Description

https://leetcode.com/problems/restore-the-array-from-adjacent-pairs/

```
There is an integer array nums that consists of n unique elements, but you have forgotten it.
However, you do remember every pair of adjacent elements in nums.

You are given a 2D integer array adjacentPairs of size n - 1 where each adjacentPairs[i] = [ui, vi]
indicates that the elements ui and vi are adjacent in nums.

It is guaranteed that every adjacent pair of elements nums[i] and nums[i+1] will exist in adjacentPairs,
either as [nums[i], nums[i+1]] or [nums[i+1], nums[i]]. The pairs can appear in any order.

Return the original array nums. If there are multiple solutions, return any of them.

Example 1:

Input: adjacentPairs = [[2,1],[3,4],[3,2]]
Output: [1,2,3,4]
Explanation: This array has all its adjacent pairs in adjacentPairs.
Notice that adjacentPairs[i] may not be in left-to-right order.

Example 2:

Input: adjacentPairs = [[4,-2],[1,4],[-3,1]]
Output: [-2,4,1,-3]
Explanation: There can be negative numbers.
Another solution is [-3,1,4,-2], which would also be accepted.

Example 3:

Input: adjacentPairs = [[100000,-100000]]
Output: [100000,-100000]

Constraints:

nums.length == n
adjacentPairs.length == n - 1
adjacentPairs[i].length == 2
2 <= n <= 10^5
-10^5 <= nums[i], ui, vi <= 10^5
There exists some nums that has adjacentPairs as its pairs.
```

## Observations

Think of the problem as a **graph / chain reconstruction** problem.

Each number is a **node**, and each adjacent pair is an **undirected edge** between two nodes.
Since `nums` is a linear array (a path, not a cycle), the resulting graph is a **simple path graph**:

- Every internal node has exactly **2 neighbors**.
- The two **endpoints** of the array have exactly **1 neighbor**.

**Key insight:**

Build an adjacency list from `adjacentPairs`. The start (or end) of the array is the node that has only **1 neighbor** — there are exactly 2 such nodes (the two ends of the array).

**Reconstruction steps:**

1. Build an adjacency map: for each pair `[u, v]`, add `v` to neighbors of `u`, and `u` to neighbors of `v`.
2. Find a starting node — any node whose neighbor list has size **1** (it's an endpoint).
3. Traverse the chain from that starting node, always moving to the neighbor that was not previously visited (like walking a linked list).
4. Collect nodes in traversal order — this is the restored array.

**Time complexity:** `O(N)` — one pass to build the map, one pass to traverse.

**Space complexity:** `O(N)` — for the adjacency map and result array.

## Tags

array, graph, hash map, depth-first search
