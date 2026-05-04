## Problem

https://leetcode.com/problems/rotate-image/description

Given an **n x n** 2D matrix representing an image, rotate the image by **90 degrees clockwise**.

You must rotate the image **in-place**, meaning you have to modify the input 2D matrix directly. **DO NOT** allocate another 2D matrix and do the rotation.

### Example 1:
```
Input:  matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]
```

### Example 2:
```
Input:  matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
```

### Constraints:
- `n == matrix.length == matrix[i].length`
- `1 <= n <= 20`
- `-1000 <= matrix[i][j] <= 1000`

## Observations

1. **Rotation by 90° Clockwise = Transpose + Reverse Rows**
   - First, transpose the matrix (swap elements across the diagonal)
   - Then, reverse each row to achieve the clockwise rotation
   - This is equivalent to rotating the entire matrix 90° clockwise

2. **Why this works (Mathematical insight):**
   - After transposing: element at position `(i, j)` moves to `(j, i)`
   - After reversing rows: element at position `(j, i)` moves to `(j, n-1-i)`
   - Combined effect: position `(i, j)` → `(j, n-1-i)`, which is exactly a 90° clockwise rotation

3. **In-place optimization:**
   - Both transpose and row reversal can be done in-place without extra O(n²) space
   - Time complexity: O(n²) - we process each element exactly twice
   - Space complexity: O(1) - only swapping variables, no extra data structures

4. **Visual example for n=3:**
   ```
   Original:        After Transpose:    After Row Reverse:
   1 2 3            1 4 7               7 4 1
   4 5 6      →     2 5 8         →     8 5 2
   7 8 9            3 6 9               9 6 3
   ```

## Solution

```python
class Solution:
    def rotate(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        n = len(matrix)
        
        # Step 1: Transpose the matrix in-place
        # Swap elements across the diagonal: matrix[i][j] ↔ matrix[j][i]
        for i in range(n):
            for j in range(i + 1, n):
                matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]
        
        # Step 2: Reverse each row in-place
        # This converts the transpose into a 90° clockwise rotation
        for i in range(n):
            matrix[i].reverse()
```

### Detailed Explanation:

**Step 1: Transpose the Matrix**
```python
for i in range(n):
    for j in range(i + 1, n):
        matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]
```
- We iterate through the upper triangle of the matrix (above the main diagonal)
- For each pair `(i, j)` where `i < j`, we swap `matrix[i][j]` with `matrix[j][i]`
- This transforms the matrix so that rows become columns and columns become rows
- The loop starts at `j = i + 1` to avoid processing the same pair twice

**Step 2: Reverse Each Row**
```python
for i in range(n):
    matrix[i].reverse()
```
- Python's `list.reverse()` reverses the row in-place
- This step converts the transposed matrix into the final rotated form
- Combined with the transpose, this achieves the 90° clockwise rotation

### Complexity Analysis:
- **Time Complexity:** O(n²) - We visit each element twice (once for transpose, once for reversal)
- **Space Complexity:** O(1) - Only constant extra space for the swap operation

### Alternative Approaches:

**Approach 2: Layer-by-Layer Rotation**
- Rotate the matrix layer by layer from outside to inside
- Rotate 4 elements at a time in each layer
- Time: O(n²), Space: O(1)
- More complex implementation but illustrates the geometric rotation directly

**Approach 3: Using Extra Space**
- Create a new matrix and place elements in rotated positions
- Time: O(n²), Space: O(n²)
- Simple but violates the in-place constraint

# Tags

- Array
- Matrix
- In-place
- Transpose
- 90 Degree Rotation
- Medium Difficulty

