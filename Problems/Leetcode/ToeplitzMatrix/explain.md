## Problem

https://leetcode.com/problems/toeplitz-matrix/description/

```
Given an m x n matrix, return true if the matrix is Toeplitz. Otherwise, return false.

A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same elements.

Example 1:

Input: matrix = [[1,2,3,4],[5,1,2,3],[9,5,1,2]]
Output: true
Explanation:
In the above grid, the diagonals are:
"[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]".
In each diagonal all elements are the same, so the answer is True.

Example 2:

Input: matrix = [[1,2],[2,2]]
Output: false
Explanation:
The diagonal "[1, 2]" has different elements.

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 20
0 <= matrix[i][j] <= 99

Follow up:

What if the matrix is stored on disk, and the memory is limited such that you can only load at most one row of the matrix into the memory at once?
What if the matrix is so large that you can only load up a partial row into the memory at once?
```

## Observations

1. **Toeplitz Matrix Definition**: A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same elements. This means elements along each diagonal line (where `row - col` is constant) must be identical.

2. **Diagonal Patterns**: In a Toeplitz matrix, there are multiple diagonals:
   - Main diagonal and diagonals above it: Start from positions `(0, 0)`, `(0, 1)`, `(0, 2)`, etc.
   - Diagonals below the main diagonal: Start from positions `(1, 0)`, `(2, 0)`, `(3, 0)`, etc.

3. **Diagonal Direction**: All diagonals move in the same direction: down-right (increment both row and column by 1).

4. **Algorithm Approach**: We need to check each diagonal by:
   - Starting from each position on the first row (top edge)
   - Starting from each position on the first column (left edge)
   - Following the diagonal path and verifying all elements are the same

5. **Edge Cases**: 
   - Single element matrices are always Toeplitz
   - Single row or single column matrices are always Toeplitz

## Tags

- Matrix
- Array
- Two Pointers

