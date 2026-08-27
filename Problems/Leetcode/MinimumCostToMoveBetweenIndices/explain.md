## Problem

https://leetcode.com/problems/minimum-cost-to-move-between-indices/description/

Given a strictly increasing integer array `nums`, two move types from index `x`:
1. Jump to **any** index `y` with cost `|nums[x] - nums[y]|`
2. Jump to `closest(x)` (the adjacent index minimizing `|nums[x] - nums[y]|`, tie-break smaller) with cost `1`

For queries `[l, r]`, find the minimum total cost to travel from `l` to `r`.

---

## Key Insight: Large Jumps Are Never Helpful

**Claim:** Walking edge-by-edge from `l` to `r` is always at least as good as any large jump.

**Proof:** A direct jump from `i` to `j` (j > i+1) costs `nums[j] - nums[i]`, which equals the sum of `d[k] = nums[k+1] - nums[k]` for `k` in `[i, j-1]`. Walking edge-by-edge costs at most `d[k]` per edge (sometimes 1 if `closest` applies), so it's always ≤ the direct jump.

Therefore the **optimal path is always a sequence of adjacent steps**, and we only need to decide the cost of each edge traversal.

---

## Per-Edge Cost

For each edge between index `i` and `i+1`, define:

- `right_cost[i]` = cost to move from `i` → `i+1`
  - `1` if `closest(i) == i+1` (the closest move goes right)
  - `nums[i+1] - nums[i]` otherwise
- `left_cost[i]` = cost to move from `i+1` → `i`
  - `1` if `closest(i+1) == i` (the closest move goes left)
  - `nums[i+1] - nums[i]` otherwise

Computing `closest(i)`:
- `i == 0`: only right neighbor → `closest(0) = 1`
- `i == n-1`: only left neighbor → `closest(n-1) = n-2`
- Otherwise: compare `nums[i] - nums[i-1]` vs `nums[i+1] - nums[i]`; pick smaller (tie → left, i.e., `i-1`)

---

## Algorithm

1. For each edge, compute `right_cost[i]` and `left_cost[i]`.
2. Build prefix sums `prefix_right` and `prefix_left`.
3. Answer each query `[l, r]` in O(1):
   - `l == r`: cost = `0`
   - `l < r`: cost = `prefix_right[r] - prefix_right[l]`
   - `l > r`: cost = `prefix_left[l] - prefix_left[r]`

**Time:** O(n + q) &nbsp; **Space:** O(n)

---

## Walkthrough

`nums = [0, 2, 3, 9]`, so `d = [2, 1, 6]`

| i | closest(i) | right_cost[i] | left_cost[i] |
|---|-----------|--------------|-------------|
| 0 | 1         | **1**        | 2           |
| 1 | 2         | **1**        | 1           |
| 2 | 1         | 6            | **1**       |
| 3 | 2         | —            | **1**       |

`prefix_right = [0, 1, 2, 8]`  
`prefix_left  = [0, 2, 3, 4]`

- `[3,0]` (l>r): `prefix_left[3] - prefix_left[0] = 4` ✓  
- `[1,2]` (l<r): `prefix_right[2] - prefix_right[1] = 1` ✓  
- `[2,0]` (l>r): `prefix_left[2] - prefix_left[0] = 3` ✓

