## Problem

https://leetcode.com/problems/shift-2d-grid/description/

```
Given a 2D grid of size m x n and an integer k. You need to shift the grid k times.

In one shift operation:

Element at grid[i][j] moves to grid[i][j + 1].
Element at grid[i][n - 1] moves to grid[i + 1][0].
Element at grid[m - 1][n - 1] moves to grid[0][0].
Return the 2D grid after applying shift operation k times.

Example 1:

Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 1
Output: [[9,1,2],[3,4,5],[6,7,8]]

Example 2:

Input: grid = [[3,8,1,9],[19,7,2,5],[4,6,11,10],[12,0,21,13]], k = 4
Output: [[12,0,21,13],[3,8,1,9],[19,7,2,5],[4,6,11,10]]

Example 3:

Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 9
Output: [[1,2,3],[4,5,6],[7,8,9]]

Constraints:

m == grid.length
n == grid[i].length
1 <= m <= 50
1 <= n <= 50
-1000 <= grid[i][j] <= 1000
0 <= k <= 100
```

## Observations

1. **Pattern Recognition**: The shifting operation moves each element to the right, wrapping around rows and from the last row back to the first row. This creates a circular shift pattern.

2. **2D to 1D Mapping**: We can think of the 2D grid as a flattened 1D array where element at position `(i, j)` maps to index `i * n + j` in the 1D representation.

3. **Circular Shift Optimization**: Instead of performing k individual shifts (which could be expensive), we can:
   - Flatten the grid to 1D
   - Apply a circular shift by k positions
   - Convert back to 2D

4. **Modulo Optimization**: Since shifting by `m * n` positions brings us back to the original state, we only need to shift by `k % (m * n)` positions.

5. **Reversal Technique**: The solution uses a clever triple-reversal technique to achieve the circular shift:
   - Reverse the first `(total_elements - k)` elements
   - Reverse the last `k` elements  
   - Reverse the entire array
   
   This is equivalent to rotating the array to the right by k positions.

## Solution

The solution uses an elegant approach combining array flattening and the reversal technique for rotation:

### Algorithm Steps:

1. **Flatten the Grid**: Convert the 2D grid into a 1D array by concatenating all rows.

2. **Optimize k**: Use `k %= (m * n)` to handle cases where k is larger than the total number of elements.

3. **Apply Reversal Rotation**: Use the three-step reversal technique:
   ```python
   # Split at position (m*n - k) and reverse both parts, then reverse the whole array
   arr = (arr[0:m*n - k][::-1] + arr[m*n - k:][::-1])[::-1]
   ```

4. **Reconstruct 2D Grid**: Map each element back to its 2D position using:
   - Row index: `i // n` 
   - Column index: `i % n`

### Time Complexity: O(m × n)
- Flattening: O(m × n)
- Reversal operations: O(m × n) 
- Reconstruction: O(m × n)

### Space Complexity: O(m × n)
- Additional array to store flattened grid

### Example Walkthrough:
For `grid = [[1,2,3],[4,5,6],[7,8,9]]`, `k = 1`:
1. Flatten: `[1,2,3,4,5,6,7,8,9]`
2. k = 1 % 9 = 1
3. Split at index 8: `[1,2,3,4,5,6,7,8]` and `[9]`
4. Reverse parts: `[8,7,6,5,4,3,2,1]` and `[9]`
5. Concatenate and reverse: `[9,1,2,3,4,5,6,7,8]`
6. Reconstruct 2D: `[[9,1,2],[3,4,5],[6,7,8]]`

# Tags
Array, Matrix, Simulation, Two Pointers

