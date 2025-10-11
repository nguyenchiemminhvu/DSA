## Problem

https://leetcode.com/problems/search-a-2d-matrix/

```
You are given an m x n integer matrix matrix with the following two properties:

Each row is sorted in non-decreasing order.
The first integer of each row is greater than the last integer of the previous row.
Given an integer target, return true if target is in matrix or false otherwise.

You must write a solution in O(log(m * n)) time complexity.

Example 1:

Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true

Example 2:

Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 100
-104 <= matrix[i][j], target <= 104
```

## Observations

1. **Matrix Properties**: The matrix has two key properties:
   - Each row is sorted in non-decreasing order
   - The first element of each row is greater than the last element of the previous row
   
2. **Linear Structure**: Due to these properties, if we "flatten" the matrix by concatenating all rows, we get a sorted array. This means we can treat the 2D matrix as a 1D sorted array conceptually.

3. **Binary Search Opportunity**: Since the data is effectively sorted in a linear fashion, we can apply binary search with O(log(m*n)) time complexity.

4. **Index Mapping**: The key insight is converting between 1D index and 2D coordinates:
   - Given a 1D index `i` in a matrix with `n` columns: `row = i // n`, `col = i % n`
   - This allows us to perform binary search on indices while accessing 2D matrix elements

5. **Search Space**: Total elements = m × n, so our search space is from index 0 to (m×n - 1)

## Solution

The solution uses **binary search** on the conceptual 1D representation of the 2D matrix:

**Algorithm:**
1. Calculate total elements: `total = m × n`
2. Set search boundaries: `left = 0`, `right = total - 1`
3. While `left <= right`:
   - Calculate middle index: `mid = left + (right - left) // 2`
   - Convert 1D index to 2D coordinates: `row = mid // n`, `col = mid % n`
   - Compare `matrix[row][col]` with target:
     - If equal: return True
     - If target is smaller: search left half (`right = mid - 1`)
     - If target is larger: search right half (`left = mid + 1`)
4. If not found, return False

**Example Walkthrough:**
```
Matrix: [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Conceptual 1D array: [1,3,5,7,10,11,16,20,23,30,34,60]
Indices:              0 1 2 3  4  5  6  7  8  9 10 11

left=0, right=11, mid=5 → matrix[5//4][5%4] = matrix[1][1] = 11 > 3
left=0, right=4, mid=2 → matrix[2//4][2%4] = matrix[0][2] = 5 > 3  
left=0, right=1, mid=0 → matrix[0//4][0%4] = matrix[0][0] = 1 < 3
left=1, right=1, mid=1 → matrix[1//4][1%4] = matrix[0][1] = 3 = 3 ✓
```

**Time Complexity:** O(log(m×n)) - binary search on m×n elements
**Space Complexity:** O(1) - only using constant extra space

## Tags

array, binary search