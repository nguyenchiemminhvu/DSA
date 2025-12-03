## Problem

https://leetcode.com/problems/matrix-similarity-after-cyclic-shifts/description/

```
You are given an m x n integer matrix mat and an integer k. The matrix rows are 0-indexed.

The following process happens k times:
- Even-indexed rows (0, 2, 4, ...) are cyclically shifted to the left.
- Odd-indexed rows (1, 3, 5, ...) are cyclically shifted to the right.

Return true if the final modified matrix after k steps is identical to the original matrix, and false otherwise.

Example 1:
Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 4
Output: false

Example 2:
Input: mat = [[1,2,1,2],[5,5,5,5],[6,3,6,3]], k = 2
Output: true

Example 3:
Input: mat = [[2,2],[2,2]], k = 3
Output: true

Constraints:
- 1 <= mat.length <= 25
- 1 <= mat[i].length <= 25
- 1 <= mat[i][j] <= 25
- 1 <= k <= 50
```

## Observations

1. **Cyclic Shift Pattern**:
   - Even-indexed rows shift LEFT (elements move towards index 0)
   - Odd-indexed rows shift RIGHT (elements move towards the end)
   - The process is repeated k times

2. **Key Insight - Modulo Optimization**:
   - Since cyclic shifts are periodic, shifting k times is equivalent to shifting `k % n` times (where n is the row length)
   - If k is a multiple of n, the row returns to its original state
   - This optimization is crucial: instead of performing k shift operations, we only need `k % n` shifts

3. **Matrix Similarity Condition**:
   - The matrix is "similar" if after k complete cycles of shifts, it looks identical to the original
   - We need to check if all rows match their original positions after shifting

4. **Special Cases**:
   - If all elements in a row are identical, any shift produces the same row
   - If `k % n == 0`, no effective shift occurs, so the matrix remains unchanged

## Solution

### Approach: Simulate and Compare

The solution simulates the shifting process once (optimized with modulo) and compares the result with the original matrix.

**Algorithm**:
1. Optimize k by taking `k % len(mat[0])` to avoid redundant full cycles
2. For each row in the matrix:
   - If row index is even (0, 2, 4...), shift left by k positions
   - If row index is odd (1, 3, 5...), shift right by k positions
3. Compare the transformed matrix with the original

**Helper Functions**:
- `shift_left(arr, k)`: Takes last `n-k` elements and moves them to the front
  - Example: `[1,2,3,4]` shifted left by 2 → `[3,4,1,2]`
  - Implementation: `arr[k:] + arr[0:k]`
  
- `shift_right(arr, k)`: Takes first `k` elements and moves them to the end
  - Example: `[1,2,3,4]` shifted right by 2 → `[3,4,1,2]`
  - Implementation: `arr[n-k:] + arr[0:n-k]`

**Code Walkthrough**:
```python
class Solution:
    def areSimilar(self, mat: List[List[int]], k: int) -> bool:
        def shift_right(arr: List[int], k: int) -> List[int]:
            n = len(arr)
            return (arr[n-k:] + arr[0:n-k])
        
        def shift_left(arr: List[int], k: int) -> List[int]:
            n = len(arr)
            return (arr[k:] + arr[0:k])
        
        # Optimize k: only need k % n shifts
        k %= len(mat[0])
        
        # Build the shifted matrix
        another = []
        is_left = True  # Start with even index (shift left)
        
        for i in range(len(mat)):
            if is_left:
                another.append(shift_left(mat[i], k))
            else:
                another.append(shift_right(mat[i], k))
            is_left = not is_left  # Alternate between even/odd
        
        # Compare original with shifted matrix
        return mat == another
```

**Note on the code**: The variable `is_left` starts as `True` because row index 0 (even) should shift left. However, the logic has a bug - it should toggle based on whether the index is even or odd, not toggle every iteration. A corrected version would be:

```python
for i in range(len(mat)):
    if i % 2 == 0:  # Even index
        another.append(shift_left(mat[i], k))
    else:  # Odd index
        another.append(shift_right(mat[i], k))
```

**Complexity Analysis**:
- Time Complexity: O(m × n) where m is the number of rows and n is the number of columns
  - We iterate through each row once
  - Each shift operation creates a new list in O(n) time
- Space Complexity: O(m × n) for storing the transformed matrix

# Tags
#array #matrix #simulation #cyclic-shift

