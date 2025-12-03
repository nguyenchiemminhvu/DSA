## Problem

https://leetcode.com/problems/determine-whether-matrix-can-be-obtained-by-rotation/description/

```
Given two n x n binary matrices mat and target, return true if it is possible to make mat equal to target by rotating mat in 90-degree increments, or false otherwise.

Example 1:
Input: mat = [[0,1],[1,0]], target = [[1,0],[0,1]]
Output: true
Explanation: We can rotate mat 90 degrees clockwise to make mat equal target.

Example 2:
Input: mat = [[0,1],[1,1]], target = [[1,0],[0,1]]
Output: false
Explanation: It is impossible to make mat equal to target by rotating mat.

Example 3:
Input: mat = [[0,0,0],[0,1,0],[1,1,1]], target = [[1,1,1],[0,1,0],[0,0,0]]
Output: true
Explanation: We can rotate mat 90 degrees clockwise two times to make mat equal target.

Constraints:
- n == mat.length == target.length
- n == mat[i].length == target[i].length
- 1 <= n <= 10
- mat[i][j] and target[i][j] are either 0 or 1.
```

## Observations

1. **Rotation Properties**:
   - A matrix can be rotated 90° clockwise 4 times to return to its original position
   - After 0°, 90°, 180°, or 270° rotation, the matrix might match the target
   - We need to check at most 4 rotations

2. **90° Clockwise Rotation Algorithm**:
   - **Step 1**: Transpose the matrix (swap elements across the main diagonal)
     - Element at position `(i, j)` moves to position `(j, i)`
   - **Step 2**: Reverse each row
   - This two-step process achieves a 90° clockwise rotation

3. **Rotation Example**:
   ```
   Original:       After Transpose:    After Reverse Rows:
   [1, 2, 3]       [1, 4, 7]          [7, 4, 1]
   [4, 5, 6]  -->  [2, 5, 8]     -->  [8, 5, 2]
   [7, 8, 9]       [3, 6, 9]          [9, 6, 3]
   ```

4. **Edge Cases**:
   - The matrices are already equal (0° rotation)
   - Single element matrix (1x1)
   - Matrices can never match regardless of rotation

## Solution

### Approach: Simulate 4 Rotations

**Algorithm**:
1. Implement a helper function `rotate(mat)` that rotates the matrix 90° clockwise in-place
2. Implement a helper function `equal(a, b)` to compare two matrices
3. Perform up to 4 rotations, checking after each rotation if `mat` equals `target`
4. Return `True` if any rotation matches, otherwise `False`

**Why 4 Rotations?**
- 0° rotation: Original matrix
- 90° rotation: First rotation
- 180° rotation: Second rotation
- 270° rotation: Third rotation
- 360° rotation: Back to original (same as 0°)

So we only need to check 4 states.

### Implementation Details

```python
class Solution:
    def findRotation(self, mat: List[List[int]], target: List[List[int]]) -> bool:
        def equal(a: List[List[int]], b: List[List[int]]) -> bool:
            na, nb = len(a), len(b)
            if na != nb:
                return False
            return all(a[i] == b[i] for i in range(na))
        
        def rotate(mat: List[List[int]]) -> None:
            n = len(mat)
            # Step 1: Transpose the matrix
            for i in range(n):
                for j in range(i, n):
                    mat[i][j], mat[j][i] = mat[j][i], mat[i][j]
            # Step 2: Reverse each row
            for i in range(n):
                mat[i].reverse()
        
        # Check 4 possible rotations (0°, 90°, 180°, 270°)
        for _ in range(4):
            rotate(mat)
            if equal(mat, target):
                return True
        return False
```

**Step-by-Step Walkthrough (Example 1)**:

Initial: `mat = [[0,1],[1,0]]`, `target = [[1,0],[0,1]]`

1. **First rotation (90°)**:
   - Transpose: `[[0,1],[1,0]]` → `[[0,1],[1,0]]`
   - Reverse rows: `[[0,1],[1,0]]` → `[[1,0],[0,1]]`
   - Compare with target `[[1,0],[0,1]]`: **Match!** ✓
   - Return `True`

**Complexity Analysis**:

- **Time Complexity**: O(n²)
  - We perform at most 4 rotations
  - Each rotation involves:
    - Transpose: O(n²) to swap elements
    - Reverse rows: O(n²) to reverse n rows of length n
  - Each comparison: O(n²) to compare all elements
  - Total: O(4 × n²) = O(n²)

- **Space Complexity**: O(1)
  - The rotation is done in-place
  - Only using a few variables for iteration
  - No additional data structures proportional to input size

### Alternative Approaches

1. **Generate all 4 rotations without modifying original**:
   - Create 4 different rotated versions and compare each
   - Space: O(n²) to store rotated copies

2. **Direct rotation formula**:
   - For 90° rotation: `new[j][n-1-i] = old[i][j]`
   - For 180° rotation: `new[n-1-i][n-1-j] = old[i][j]`
   - For 270° rotation: `new[n-1-j][i] = old[i][j]`
   - Check each transformation directly without creating new matrices

# Tags
Matrix, Simulation, Array Manipulation, In-place Algorithm

