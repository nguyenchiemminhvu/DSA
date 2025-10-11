## Problem

https://leetcode.com/problems/search-a-2d-matrix-ii/description/

```
Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.

Example 1:

Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
Output: true

Example 2:

Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
Output: false

Constraints:

m == matrix.length
n == matrix[i].length
1 <= n, m <= 300
-109 <= matrix[i][j] <= 109
All the integers in each row are sorted in ascending order.
All the integers in each column are sorted in ascending order.
-109 <= target <= 109
```

## Observations

1. **Matrix Properties**: The matrix has two important properties:
   - Each row is sorted in ascending order from left to right
   - Each column is sorted in ascending order from top to bottom

2. **Brute Force Approach**: We could search every element, but that would be O(m*n) time complexity.

3. **Row-wise Binary Search**: Since each row is sorted, we can apply binary search on each row individually. This gives us O(m * log n) time complexity.

4. **Alternative Optimal Approach**: There's a more elegant O(m + n) solution that starts from top-right or bottom-left corner, but the given solution uses the row-wise binary search approach.

5. **Search Space**: For each row, we can eliminate half the elements in each binary search step.

## Solution

The provided solution uses a **row-wise binary search** approach:

```python
class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        m = len(matrix)
        n = len(matrix[0])

        def binary_search(arr: List[int], target: int) -> bool:
            left = 0
            right = len(arr) - 1
            while left <= right:
                mid = left + (right - left) // 2
                if target == arr[mid]:
                    return True
                if target < arr[mid]:
                    right = mid - 1
                else:
                    left = mid + 1
            return False

        for row in matrix:
            if binary_search(row, target):
                return True
        return False
```

**Algorithm Explanation:**

1. **Binary Search Function**: Implements standard binary search on a 1D array
   - Uses two pointers (`left` and `right`) to maintain search boundaries
   - Calculates `mid` using `left + (right - left) // 2` to avoid integer overflow
   - Returns `True` if target is found, `False` otherwise

2. **Main Logic**: 
   - Iterates through each row of the matrix
   - Applies binary search on each row since rows are sorted
   - Returns `True` immediately if target is found in any row
   - Returns `False` if target is not found in any row

**Time Complexity**: O(m * log n)
- m iterations for each row
- log n time for binary search in each row of length n

**Space Complexity**: O(1)
- Only using constant extra space for variables

**Alternative O(m + n) Approach**: Start from top-right corner (or bottom-left), move left if current element is greater than target, move down if current element is smaller than target. This leverages both row and column sorting properties more efficiently.

## Tags

array, binary search