## Problem

https://leetcode.com/problems/path-existence-queries-in-a-graph-i/

Given `n` nodes labeled `0` to `n-1`, an integer array `nums` (sorted non-decreasing), and an integer `maxDiff`:
- An **undirected edge** exists between nodes `i` and `j` if `|nums[i] - nums[j]| <= maxDiff`.
- For each query `[u, v]`, determine whether a **path** exists between nodes `u` and `v`.

Return a boolean array `answer` where `answer[i]` is `true` if a path exists for the i-th query.

---

## Observations

1. **Sorted array → local connectivity check suffices.**  
   Because `nums` is sorted in non-decreasing order, for any two nodes `i < j`:
   $$nums[j] - nums[i] \geq nums[i+1] - nums[i]$$
   So if consecutive nodes `i` and `i+1` are **not** connected (gap > `maxDiff`), then **no** node on the left side of that gap can ever reach any node on the right side — the gap only grows larger for further-apart indices.

2. **Edges form contiguous segments.**  
   Connectivity in this graph reduces to finding "segments" of consecutive indices where each adjacent pair satisfies `nums[i+1] - nums[i] <= maxDiff`. Nodes within the same segment are all reachable from each other (via a chain of edges), and nodes in different segments are completely disconnected.

3. **Path existence = same segment membership.**  
   A path exists between `u` and `v` if and only if they belong to the same contiguous segment. This avoids building the full graph entirely.

---

## Solution Explanation

The solution assigns a **group ID** to each node in a single left-to-right pass:

```
groups = [0] * n
cur_id = 0
for i in range(1, n):
    if nums[i] - nums[i-1] > k:   # gap too large → new group
        cur_id += 1
    groups[i] = cur_id
```

- Start all nodes in group `0`.
- Scan from index `1` to `n-1`. Whenever the difference between consecutive values exceeds `maxDiff` (called `k` here), increment `cur_id` to start a new group.
- Each node is stamped with its group ID.

For each query `[u, v]`, the answer is simply:
```
groups[u] == groups[v]
```

**Why this is correct:**  
A gap `nums[i] - nums[i-1] > maxDiff` acts as an impassable barrier. Because the array is sorted, all values to the left of index `i` are smaller and all values to the right are larger — no indirect path can ever bridge this barrier. Therefore, group membership fully characterizes connected components.

**Complexity:**
- **Time:** O(n + q) — one pass to build groups, one pass over queries.
- **Space:** O(n) — for the groups array.
