## Problem

https://leetcode.com/problems/minimum-xor-path-in-a-grid/

```
You are given a 2D integer array grid of size m * n.

You start at the top-left cell (0, 0) and want to reach the bottom-right cell (m - 1, n - 1).

At each step, you may move either right or down.

The cost of a path is defined as the bitwise XOR of all the values in the cells along that path, including the start and end cells.

Return the minimum possible XOR value among all valid paths from (0, 0) to (m - 1, n - 1).

Example 1:

Input: grid = [[1,2],[3,4]]
Output: 6
Explanation:
- (0, 0) -> (0, 1) -> (1, 1) with XOR: 1 XOR 2 XOR 4 = 7
- (0, 0) -> (1, 0) -> (1, 1) with XOR: 1 XOR 3 XOR 4 = 6
The minimum XOR value among all valid paths is 6.

Example 2:

Input: grid = [[6,7],[5,8]]
Output: 9
Explanation:
- (0, 0) -> (0, 1) -> (1, 1) with XOR: 6 XOR 7 XOR 8 = 9
- (0, 0) -> (1, 0) -> (1, 1) with XOR: 6 XOR 5 XOR 8 = 11
The minimum XOR value among all valid paths is 9.

Example 3:

Input: grid = [[2,7,5]]
Output: 0
Explanation:
- (0, 0) -> (0, 1) -> (0, 2) with XOR: 2 XOR 7 XOR 5 = 0
The XOR value of this path is 0, which is the minimum possible.

Constraints:

1 <= m == grid.length <= 1000
1 <= n == grid[i].length <= 1000
m * n <= 1000
0 <= grid[i][j] <= 1023
```

## Ideas

1. **Brute force is too slow**: Every path has `m + n - 2` moves and there are `C(m + n - 2, m - 1)` paths. For grids like `31 x 32` that count is astronomically large, so enumerating paths is not an option.

2. **XOR is not monotone**: The minimum XOR of a path cannot be found by keeping only the smallest prefix XOR at each cell. Two prefixes that are both "small" can lead to very different final XOR values after more cells are XORed in. So each cell must remember every XOR value that can actually reach it.

3. **Values are small**: Every `grid[i][j]` is at most `1023`, so any XOR of cell values is also in `[0, 1023]`. That means each cell has at most `1024` distinct reachable XOR values, which keeps the state space bounded.

4. **Set-based DP**: Let `S(i, j)` be the set of XOR values of all paths from `(0, 0)` to `(i, j)`, including both endpoints. Then:
   - `S(0, 0) = {grid[0][0]}`
   - `S(i, j) = { v XOR grid[i][j] : v in S(i - 1, j) or v in S(i, j - 1) }`
   - The answer is `min(S(m - 1, n - 1))`

5. **Complexity**: With `m * n <= 1000` and at most `1024` values per cell, the work is about `1000 * 1024 ~ 10^6` operations. Space is `O(m * n * 1024)` in the worst case. It can be reduced to `O(n * 1024)` by keeping only the previous row.

6. **Alternative**: Use a boolean array of size `1024` per cell instead of a set. Moving a value through a cell is then an XOR-permutation of indices, which is equivalent and sometimes simpler to vectorize.

## Solution

The solution in [solve.py](./solve.py) uses the set-based DP above:

1. Fill the first row and first column, where each cell has exactly one reachable XOR value along the single straight path.
2. For every other cell, union the sets from the cell above and the cell to the left, then XOR each value with the current cell.
3. Return the minimum value in the bottom-right set.

It was checked against the three examples and 2,000 random grids compared with brute force, and all results matched.

## Tags

array, dynamic programming, bit manipulation, matrix
