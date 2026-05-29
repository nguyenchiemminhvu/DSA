## Problem

https://leetcode.com/problems/count-submatrices-with-all-ones/description

Given an `m x n` binary matrix `mat`, return the **number of submatrices that have all ones**.

A submatrix is a contiguous rectangular region of the matrix. We need to count every such rectangle whose cells are all `1`.

---

## Observations

1. **Brute force** is O(m² × n²) — fix top-left and bottom-right corners, verify all cells. Too slow for 150×150.

2. **Histogram reduction**: For each row `r`, define `height[c]` = number of consecutive `1`s ending at row `r` in column `c`.  
   If `mat[r][c] == 0`, then `height[c] = 0`; otherwise `height[c] += 1`.  
   With this, any valid submatrix whose **bottom row is row `r`** corresponds to choosing a column range `[l, r_col]` and a height `h ≤ min(height[l..r_col])`. The count of such submatrices for a fixed column range is `min(height[l..r_col])`.

3. **Summing over all column ranges** (the commented O(n²) approach):
   ```
   for each row:
       for l in range(n):
           for r in range(l, n):
               res += min(height[l..r])
   ```
   This is O(m × n²) — acceptable for n=150 but can be improved.

4. **Contribution technique with monotonic stack** (the optimized approach):  
   Instead of iterating column ranges, ask: *for each column `i`, in how many ranges is `height[i]` the minimum?*  
   - Let `left[i]` = the nearest index to the left where `height[left[i]] < height[i]` (strictly less), defaulting to `-1`.  
   - Let `right[i]` = the nearest index to the right where `height[right[i]] < height[i]` (strictly less), defaulting to `n`.  
   - Column `i` is the **leftmost minimum** (to break ties and avoid double-counting) in any column range `[l, r]` where `left[i] < l ≤ i` and `i ≤ r < right[i]`.  
   - Number of such ranges = `(i - left[i]) × (right[i] - i)`.  
   - Each such range contributes `height[i]` submatrices (one for each possible number of rows from 1 to `height[i]`).  
   - Total contribution of column `i` = `height[i] × (i - left[i]) × (right[i] - i)`.

5. **Why tie-breaking matters**: The stack condition `height[st[-1]] >= h` pops equal heights. This means when two columns share the same height, the *right* one defines the minimum for the overlapping region, ensuring no double-counting.

---

## Solution Walkthrough

```python
class Solution:
    def numSubmat(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        res = 0
        height = [0] * n

        for row in grid:
            # Step 1: Build the histogram for the current bottom row
            for i in range(n):
                if row[i] == 0:
                    height[i] = 0
                else:
                    height[i] += 1

            # Step 2: Use a monotonic stack to find left[i] and right[i]
            st = []
            left = [-1] * n   # nearest index to the left with strictly smaller height
            right = [n] * n   # nearest index to the right with strictly smaller height

            for i, h in enumerate(height):
                # Pop while stack top has height >= current (handles equal heights too)
                while st and height[st[-1]] >= h:
                    right[st[-1]] = i   # i is the first smaller-or-equal to the right
                    st.pop()
                if st:
                    left[i] = st[-1]    # nearest strictly smaller to the left
                st.append(i)

            # Step 3: Sum up contributions
            for i in range(n):
                res += height[i] * (i - left[i]) * (right[i] - i)

        return res
```

**Example trace** on `mat = [[1,0,1],[1,1,0],[1,1,0]]` after processing row 2 (0-indexed):

| col   | 0 | 1 | 2 |
|-------|---|---|---|
| height| 3 | 2 | 0 |
| left  |-1 |-1 | 1 |
| right | 1 | 2 | 2 |

- col 0: `3 × (0-(-1)) × (1-0)` = `3 × 1 × 1` = **3**
- col 1: `2 × (1-(-1)) × (2-1)` = `2 × 2 × 1` = **4**
- col 2: `0 × ...` = **0**

Running total from all rows = **13** ✓

---

## Complexity

| | Value |
|---|---|
| Time | O(m × n) — each cell is pushed/popped from the stack at most once per row |
| Space | O(n) — for `height`, `left`, `right`, and the stack |
