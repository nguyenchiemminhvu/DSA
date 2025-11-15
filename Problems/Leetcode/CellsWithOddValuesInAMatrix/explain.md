## Problem

https://leetcode.com/problems/cells-with-odd-values-in-a-matrix/description/

```
There is an m x n matrix that is initialized to all 0's. There is also a 2D array indices where each indices[i] = [ri, ci] represents a 0-indexed location to perform some increment operations on the matrix.

For each location indices[i], do both of the following:

Increment all the cells on row ri.
Increment all the cells on column ci.
Given m, n, and indices, return the number of odd-valued cells in the matrix after applying the increment to all locations in indices.

Example 1:

Input: m = 2, n = 3, indices = [[0,1],[1,1]]
Output: 6
Explanation: Initial matrix = [[0,0,0],[0,0,0]].
After applying first increment it becomes [[1,2,1],[0,1,0]].
The final matrix is [[1,3,1],[1,3,1]], which contains 6 odd numbers.

Example 2:

Input: m = 2, n = 2, indices = [[1,1],[0,0]]
Output: 0
Explanation: Final matrix = [[2,2],[2,2]]. There are no odd numbers in the final matrix.

Constraints:

1 <= m, n <= 50
1 <= indices.length <= 100
0 <= ri < m
0 <= ci < n

Follow up: Could you solve this in O(n + m + indices.length) time with only O(n + m) extra space?
```

## Observations

1. **Increment Operations**: Each operation in `indices[i] = [ri, ci]` increments:
   - All cells in row `ri`
   - All cells in column `ci`

2. **Final Cell Value**: After all operations, the value at position `[i, j]` equals:
   - Number of times row `i` was incremented + Number of times column `j` was incremented

3. **Odd Value Condition**: A cell `[i, j]` has an odd value if and only if:
   - `(row_increments[i] + col_increments[j]) % 2 == 1`
   - This happens when one of them is odd and the other is even

4. **Space Optimization**: Instead of simulating the entire matrix, we only need to track:
   - How many times each row is incremented
   - How many times each column is incremented

5. **Time Complexity**: The solution achieves O(m × n + indices.length) time and O(m + n) space, meeting the follow-up requirement.

## Solution

1. **Initialize Counters**: Create arrays `rows` and `cols` to track how many times each row and column gets incremented.

2. **Process Operations**: For each `[r, c]` in indices, increment the counters for row `r` and column `c`.

3. **Count Odd Cells**: For each cell position `[i, j]`:
   - Calculate the final value: `rows[i] + cols[j]`
   - Check if it's odd using `(rows[i] + cols[j]) & 1`
   - The bitwise AND with 1 returns 1 if the number is odd, 0 if even

4. **Return Result**: Sum up all odd cells.

**Key Insights:**
- We don't need to simulate the actual matrix operations
- Only the parity (odd/even) of increment counts matters
- Bitwise operations are more efficient than modulo for checking odd/even

**Time Complexity:** O(m × n + indices.length)
**Space Complexity:** O(m + n)

# Tags
Array, Matrix, Simulation, Math

