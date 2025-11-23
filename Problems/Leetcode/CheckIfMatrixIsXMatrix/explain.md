## Problem

https://leetcode.com/problems/check-if-matrix-is-x-matrix/description/

```
A square matrix is said to be an X-Matrix if both of the following conditions hold:

All the elements in the diagonals of the matrix are non-zero.
All other elements are 0.
Given a 2D integer array grid of size n x n representing a square matrix, return true if grid is an X-Matrix. Otherwise, return false.

Example 1:

Input: grid = [[2,0,0,1],[0,3,1,0],[0,5,2,0],[4,0,0,2]]
Output: true
Explanation: Refer to the diagram above. 
An X-Matrix should have the green elements (diagonals) be non-zero and the red elements be 0.
Thus, grid is an X-Matrix.

Example 2:

Input: grid = [[5,7,0],[0,3,1],[0,5,0]]
Output: false
Explanation: Refer to the diagram above.
An X-Matrix should have the green elements (diagonals) be non-zero and the red elements be 0.
Thus, grid is not an X-Matrix.

Constraints:

n == grid.length == grid[i].length
3 <= n <= 100
0 <= grid[i][j] <= 105
```

## Observations

1. **Diagonal Elements**: An X-Matrix has two diagonals:
   - Main diagonal: elements at positions (i, i) where i = 0, 1, ..., n-1
   - Anti-diagonal: elements at positions (i, n-1-i) where i = 0, 1, ..., n-1

2. **Key Conditions**:
   - All diagonal elements must be non-zero
   - All non-diagonal elements must be zero

3. **Edge Cases**:
   - For odd-sized matrices, the center element (n//2, n//2) is on both diagonals
   - Need to check both diagonals separately and all other positions

4. **Matrix Positions**:
   - Diagonal positions: (i, i) and (i, n-1-i)
   - Non-diagonal positions: all other (i, j) where j ≠ i and j ≠ n-1-i

## Solution

The solution uses a two-pass approach:

**Pass 1: Check Diagonal Elements**
```python
for i in range(n):
    if grid[i][i] == 0:          # Main diagonal check
        return False
    j = n - i - 1
    if grid[i][j] == 0:          # Anti-diagonal check
        return False
```
- Iterates through each row and checks both diagonal positions
- Main diagonal: (i, i)
- Anti-diagonal: (i, n-1-i)
- Returns False immediately if any diagonal element is 0

**Pass 2: Check Non-Diagonal Elements**
```python
for i in range(n):
    for j in range(n):
        if j != i and j != (n - i - 1):    # Not on either diagonal
            if grid[i][j] != 0:
                return False
```
- Checks all matrix positions
- Skips diagonal positions using the condition `j != i and j != (n - i - 1)`
- Returns False if any non-diagonal element is non-zero

**Time Complexity**: O(n²) - visits each element once across both passes
**Space Complexity**: O(1) - only uses constant extra space

The solution is efficient and correctly handles all cases including the center element in odd-sized matrices.

# Tags

Array, Matrix, Simulation

