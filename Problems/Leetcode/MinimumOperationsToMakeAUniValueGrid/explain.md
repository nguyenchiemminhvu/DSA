## Problem

https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/

```
You are given a 2D integer grid of size m x n and an integer x. In one operation,
you can add x to or subtract x from any element in the grid.

A uni-value grid is a grid where all the elements of it are equal.

Return the minimum number of operations to make the grid uni-value.
If it is not possible, return -1.

Example 1:
  Input: grid = [[2,4],[6,8]], x = 2
  Output: 4
  Explanation: We can make every element equal to 4 by doing the following:
  - Add x to 2 once.
  - Subtract x from 6 once.
  - Subtract x from 8 twice.
  A total of 4 operations were used.

Example 2:
  Input: grid = [[1,5],[2,3]], x = 1
  Output: 5
  Explanation: We can make every element equal to 3.

Example 3:
  Input: grid = [[1,2],[3,4]], x = 2
  Output: -1
  Explanation: It is impossible to make every element equal.

Constraints:
  m == grid.length
  n == grid[i].length
  1 <= m, n <= 10^5
  1 <= m * n <= 10^5
  1 <= x, grid[i][j] <= 10^4
```

## Observations

- Flatten the 2D grid into a 1D array — the row/column structure is irrelevant; only values matter.
- Each element can only be moved in steps of `x`, so two values `a` and `b` can only be equalized if `(a - b) % x == 0`. If any pair violates this, return `-1`. It suffices to check every element against a single reference (e.g., `arr[0]`) after sorting.
- The target value must differ from every element by a multiple of `x`. This means all elements share the same remainder when divided by `x`.
- To minimize the total number of operations (total absolute steps divided by `x`), we want to minimize `sum(|val - target|)` over all values. This is minimized when `target` is the **median** of the array.
  - The median minimizes the sum of absolute deviations (classic statistics result).
- The cost of moving `val` to `target` is `|val - target| / x` operations.

## Solution

```python
class Solution:
    def minOperations(self, grid: List[List[int]], x: int) -> int:
        # Flatten the grid into a 1D array
        arr = [val for row in grid for val in row]
        arr.sort()
        n = len(arr)

        # Check feasibility: every element must be reachable from arr[0] via steps of x
        for i in range(1, n):
            d = arr[i] - arr[0]
            if d % x != 0:
                return -1

        # The optimal target is the median (minimizes sum of absolute deviations)
        mid = arr[n // 2]

        # Count total operations
        res = 0
        for val in arr:
            res += abs(val - mid) // x
        return res
```

**Why the median?**

Given a sorted array, the sum $\sum |v_i - t|$ is minimized when $t$ is the median.
- If we shift $t$ left by one step, values to the right of $t$ each cost one more operation, while values to the left cost one less — but at the median, both sides are balanced so any shift increases total cost.
- For an even-length array, any value between the two middle elements is optimal; `arr[n // 2]` is one valid choice.

**Complexity:** $O(mn \log mn)$ for sorting, $O(mn)$ for the rest.

# Tags

`Array` `Math` `Sorting`

