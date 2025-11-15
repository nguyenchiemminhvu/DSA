## Problem

https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/

```
Given a m x n matrix grid which is sorted in non-increasing order both row-wise and column-wise, return the number of negative numbers in grid.

Example 1:

Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
Output: 8
Explanation: There are 8 negatives number in the matrix.

Example 2:

Input: grid = [[3,2],[1,0]]
Output: 0

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 100
-100 <= grid[i][j] <= 100
 

Follow up: Could you find an O(n + m) solution?
```

## Observations

1. **Matrix Properties**: The matrix is sorted in non-increasing order both row-wise and column-wise
   - Each row is sorted from largest to smallest (decreasing)
   - Each column is also sorted from largest to smallest (decreasing)

2. **Key Insight**: Since each row is sorted in decreasing order, once we find the first negative number in a row, all numbers after it will also be negative

3. **Binary Search Opportunity**: We can use binary search to efficiently find the first negative number in each row

4. **Algorithm Choice**: The solution uses a modified binary search (upper bound in reverse) to find the leftmost position where numbers become negative (< 0)

## Solution

### Approach: Binary Search on Each Row

**Time Complexity**: O(m × log n) where m is number of rows and n is number of columns  
**Space Complexity**: O(1)

#### Algorithm Steps:

1. **For each row**, use binary search to find the first negative number
2. **Binary Search Logic** (`upper_bound_reverse`):
   - Find the leftmost position where `arr[mid] < 0`
   - Since array is in decreasing order, we search from left to right
   - When `arr[mid] < 0`, we found a negative number, save this position and search left half
   - When `arr[mid] >= 0`, search right half
3. **Count negatives**: Once we find the first negative position `idx`, all numbers from `idx` to end of row are negative
4. **Add to result**: `len(row) - idx` gives us the count of negatives in current row

#### Key Function: `upper_bound_reverse`
```python
def upper_bound_reverse(arr: List[int], target) -> int:
    # Finds leftmost position where arr[i] < target
    # Returns n if no such position exists
```

#### Why This Works:
- Matrix row: `[4, 3, 2, -1]` (decreasing order)
- Target: `0`
- Binary search finds index `3` (where `-1` is located)
- Count: `4 - 3 = 1` negative number

#### Example Walkthrough:
```
Grid: [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]

Row 0: [4,3,2,-1] → first negative at index 3 → count = 4-3 = 1
Row 1: [3,2,1,-1] → first negative at index 3 → count = 4-3 = 1  
Row 2: [1,1,-1,-2] → first negative at index 2 → count = 4-2 = 2
Row 3: [-1,-1,-2,-3] → first negative at index 0 → count = 4-0 = 4

Total: 1 + 1 + 2 + 4 = 8 negatives
```

### Alternative O(m + n) Solution:
Start from top-right corner and move left/down based on current value being positive/negative.

# Tags

- Binary Search
- Matrix
- Two Pointers

