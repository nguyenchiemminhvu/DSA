## Problem

https://leetcode.com/problems/matrix-diagonal-sum/description/

```
Given a square matrix mat, return the sum of the matrix diagonals.

Only include the sum of all the elements on the primary diagonal and all the elements on the secondary diagonal that are not part of the primary diagonal.

Example 1:

Input: mat = [[1,2,3],
              [4,5,6],
              [7,8,9]]
Output: 25
Explanation: Diagonals sum: 1 + 5 + 9 + 3 + 7 = 25
Notice that element mat[1][1] = 5 is counted only once.

Example 2:

Input: mat = [[1,1,1,1],
              [1,1,1,1],
              [1,1,1,1],
              [1,1,1,1]]
Output: 8

Example 3:

Input: mat = [[5]]
Output: 5

Constraints:

n == mat.length == mat[i].length
1 <= n <= 100
1 <= mat[i][j] <= 100
```

## Observations

1. **Two Diagonals to Consider**: In a square matrix, there are two main diagonals:
   - **Primary diagonal**: Elements where row index equals column index (i.e., `mat[i][i]`)
   - **Secondary diagonal**: Elements where row index + column index equals n-1 (i.e., `mat[i][n-1-i]`)

2. **Avoid Double Counting**: For odd-sized matrices (n is odd), the center element `mat[n//2][n//2]` lies on both diagonals and should only be counted once.

3. **Diagonal Patterns**:
   - Primary diagonal: `(0,0) → (1,1) → (2,2) → ... → (n-1,n-1)`
   - Secondary diagonal: `(0,n-1) → (1,n-2) → (2,n-3) → ... → (n-1,0)`

4. **Matrix Center**: For odd n, the center element is at position `(n//2, n//2)` and belongs to both diagonals.

5. **Traversal Strategy**: We can traverse each diagonal separately using simple loops, then handle the center element case.

## Solution

The solution uses a straightforward approach with two separate loops to sum both diagonals:

**Step 1: Sum Primary Diagonal**
- Start from `(0,0)` and move diagonally down-right
- Increment both row and column indices by 1 each iteration
- Continue until we reach the bottom-right corner `(n-1,n-1)`

**Step 2: Sum Secondary Diagonal**  
- Start from `(0,n-1)` and move diagonally down-left
- Increment row index by 1, decrement column index by 1 each iteration
- Continue until we reach the bottom-left corner `(n-1,0)`

**Step 3: Handle Center Element (Odd Matrix)**
- If the matrix size is odd (`n & 1` is true), subtract the center element once
- The center element is at position `(n//2, n//2)` where `n//2` can be computed using bit shift `n >> 1`

**Example Walkthrough** with `mat = [[1,2,3],[4,5,6],[7,8,9]]`:

1. **Primary diagonal sum**: `1 + 5 + 9 = 15`
2. **Secondary diagonal sum**: `3 + 5 + 7 = 15`  
3. **Total before adjustment**: `15 + 15 = 30`
4. **Center element (counted twice)**: `mat[1][1] = 5`
5. **Final result**: `30 - 5 = 25`

**Time Complexity**: O(n) - We traverse each diagonal once
**Space Complexity**: O(1) - Only using constant extra space

**Key Implementation Details**:
- Uses bit operations: `n & 1` to check if n is odd, `n >> 1` for integer division by 2
- Simple while loops with boundary checking for safety
- Clean separation of concerns: sum diagonals first, then adjust for center

# Tags

array, matrix, math

