## Problem

https://leetcode.com/problems/lucky-numbers-in-a-matrix/description/

```
Given an m x n matrix of distinct numbers, return all lucky numbers in the matrix in any order.

A lucky number is an element of the matrix such that it is the minimum element in its row and maximum in its column.

Example 1:

Input: matrix = [[3,7,8],[9,11,13],[15,16,17]]
Output: [15]
Explanation: 15 is the only lucky number since it is the minimum in its row and the maximum in its column.

Example 2:

Input: matrix = [[1,10,4,2],[9,3,8,7],[15,16,17,12]]
Output: [12]
Explanation: 12 is the only lucky number since it is the minimum in its row and the maximum in its column.

Example 3:

Input: matrix = [[7,8],[1,2]]
Output: [7]
Explanation: 7 is the only lucky number since it is the minimum in its row and the maximum in its column.

Constraints:

m == mat.length
n == mat[i].length
1 <= n, m <= 50
1 <= matrix[i][j] <= 105.
All elements in the matrix are distinct.
```

## Observations

1. **Lucky Number Definition**: A number is "lucky" if it satisfies BOTH conditions:
   - It's the minimum element in its row
   - It's the maximum element in its column

2. **Key Insight**: Due to the constraint that all elements are distinct, there can be at most one lucky number in the entire matrix. This is because:
   - If an element is the minimum in its row, all other elements in that row are larger
   - If the same element is the maximum in its column, all other elements in that column are smaller
   - This creates a unique position where the element is simultaneously the smallest horizontally and largest vertically

3. **Approach Strategy**: 
   - Pre-compute all row minimums and column maximums
   - Check each element to see if it equals both its row minimum and column maximum
   - This avoids redundant calculations during the search

4. **Matrix Properties**:
   - All elements are distinct (no duplicates)
   - Matrix dimensions: m x n where 1 ≤ m,n ≤ 50
   - Element values: 1 ≤ matrix[i][j] ≤ 10^5

## Solution

### Algorithm Explanation

The solution uses a **precomputation + verification** approach:

1. **Precomputation Phase**:
   ```python
   rows = [min(row) for row in matrix]  # Store minimum of each row
   cols = [max(row[c] for row in matrix) for c in range(n)]  # Store maximum of each column
   ```

2. **Verification Phase**:
   - Iterate through each element in the matrix
   - Check if `matrix[i][j] == rows[i]` (minimum in row i)
   - Check if `matrix[i][j] == cols[j]` (maximum in column j)
   - If both conditions are true, add to result

### Step-by-Step Walkthrough

Example: `matrix = [[3,7,8],[9,11,13],[15,16,17]]`

1. **Calculate row minimums**: `rows = [3, 9, 15]`
2. **Calculate column maximums**: `cols = [15, 16, 17]`
3. **Check each element**:
   - `matrix[0][0] = 3`: `3 == rows[0] (3)` ✓, `3 == cols[0] (15)` ✗
   - `matrix[2][0] = 15`: `15 == rows[2] (15)` ✓, `15 == cols[0] (15)` ✓ → Lucky!

### Time & Space Complexity

- **Time Complexity**: O(m × n)
  - O(m × n) to compute row minimums
  - O(m × n) to compute column maximums  
  - O(m × n) to check each element
  - Total: O(m × n)

- **Space Complexity**: O(m + n)
  - O(m) for storing row minimums
  - O(n) for storing column maximums
  - O(1) for result (at most 1 lucky number due to distinctness)

### Alternative Approaches

1. **Brute Force**: For each element, scan its entire row and column - O(m × n × (m + n))
2. **Early Termination**: Since at most one lucky number exists, return immediately when found
3. **Set Intersection**: Find intersection of row minimums and column maximums - O(m + n)

# Tags

`Array` `Matrix` `Preprocessing` `Two-Pass Algorithm`

