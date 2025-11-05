## Problem

https://leetcode.com/problems/range-addition-ii/

```
You are given an m x n matrix M initialized with all 0's and an array of operations ops, where ops[i] = [ai, bi] means M[x][y] should be incremented by one for all 0 <= x < ai and 0 <= y < bi.

Count and return the number of maximum integers in the matrix after performing all the operations.

Example 1:

Input: m = 3, n = 3, ops = [[2,2],[3,3]]
Output: 4
Explanation: The maximum integer in M is 2, and there are four of it in M. So return 4.

Example 2:

Input: m = 3, n = 3, ops = [[2,2],[3,3],[3,3],[3,3],[2,2],[3,3],[3,3],[3,3],[2,2],[3,3],[3,3],[3,3]]
Output: 4

Example 3:

Input: m = 3, n = 3, ops = []
Output: 9

Constraints:

1 <= m, n <= 4 * 104
0 <= ops.length <= 104
ops[i].length == 2
1 <= ai <= m
1 <= bi <= n
```

## Observations

1. **Understanding the Operations**: Each operation `[ai, bi]` increments all cells `M[x][y]` where `0 <= x < ai` and `0 <= y < bi`. This means it affects a rectangular region from top-left corner `(0,0)` to `(ai-1, bi-1)`.

2. **Key Insight - Intersection Pattern**: The maximum value in the matrix will be in the region that is affected by ALL operations. This is because:
   - Each operation adds 1 to its affected region
   - The cells that get incremented the most are those that overlap with all operations
   - The overlapping region forms a rectangle from `(0,0)` to `(min_ai-1, min_bi-1)`

3. **Why Minimum Dimensions Matter**: 
   - If we have operations `[2,2]` and `[3,3]`, the intersection is `[2,2]`
   - Only cells in the `2×2` top-left region get incremented by both operations
   - Cells outside this region get incremented by fewer operations, so they have smaller values

4. **Edge Case - Empty Operations**: If no operations are performed, all cells remain 0, so all `m×n` cells are maximum (all equal to 0).

5. **Visual Example**: For `m=3, n=3, ops=[[2,2],[3,3]]`:
   ```
   Initial:     After [2,2]:    After [3,3]:
   0 0 0        1 1 0           2 2 1
   0 0 0   →    1 1 0      →    2 2 1
   0 0 0        0 0 0           1 1 1
   ```
   Maximum value is 2, appearing in 4 cells (top-left 2×2 region).

## Solution

The solution elegantly leverages the key insight that we don't need to simulate the matrix operations. Instead:

1. **Handle Empty Operations**: If `ops` is empty, return `m * n` since all cells have the same value (0).

2. **Find Intersection Dimensions**: 
   - `mina = min(op[0] for op in ops)` - minimum row range across all operations
   - `minb = min(op[1] for op in ops)` - minimum column range across all operations

3. **Calculate Result**: The intersection rectangle has dimensions `mina × minb`, which contains all cells with maximum value.

**Time Complexity**: O(k) where k is the number of operations
**Space Complexity**: O(1) - only using constant extra space

The solution is optimal because it avoids the naive O(m×n×k) approach of simulating each operation on the matrix.

# Tags

- Array
- Math
- Simulation (avoided)
- Greedy
- Matrix

