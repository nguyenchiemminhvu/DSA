## Problem

https://leetcode.com/problems/decode-the-slanted-ciphertext/description/

A string `originalText` is encoded using a slanted transposition cipher with the help of a matrix having a fixed number of rows.

The encoding process:
1. Place `originalText` in a matrix row by row, filling from left to right
2. The encoded matrix is constructed by reading diagonally:
   - Start from each column (0 to cols-1)
   - Read diagonally downward-right: (0, col), (1, col+1), (2, col+2), etc.
   - Empty cells are filled with spaces ' '
3. `encodedText` is formed by appending all characters read in this diagonal manner, column by column

**Goal:** Given `encodedText` and `rows`, decode and return the original `originalText` (without trailing spaces).

**Constraints:**
- 0 <= encodedText.length <= 10^6
- encodedText consists of lowercase English letters and spaces only
- 1 <= rows <= 1000
- originalText does not have trailing spaces
- There is only one possible originalText for each test case

**Examples:**
1. Input: encodedText = "ch   ie   pr", rows = 3 → Output: "cipher"
2. Input: encodedText = "iveo    eed   l te   olc", rows = 4 → Output: "i love leetcode"
3. Input: encodedText = "coding", rows = 1 → Output: "coding"

## Observations

1. **Reverse the diagonal reading process:** We need to reverse the encoding:
   - Reconstruct the matrix from `encodedText` by placing characters row-wise
   - Read the matrix diagonally to recover `originalText`

2. **Column count calculation:** Since `encodedText` is formed by reading diagonals and the matrix has `rows` rows, the number of columns is `cols = len(encodedText) // rows`

3. **Diagonal reading pattern:** Each diagonal starts from a unique column (0 to cols-1) at row 0, then moves down-right while staying within bounds

4. **Matrix reconstruction:** The `encodedText` is already in row-major order from the matrix, so we can directly slice it into rows of size `cols`

5. **Trailing spaces:** Remove trailing spaces from the final result since `originalText` doesn't have any

## Solution

**Algorithm:**
1. Calculate `cols = len(encodedText) // rows`
2. Reconstruct the matrix by dividing the encoded text into rows of size `cols`
3. Read the matrix diagonally for each starting column:
   - For each column `col` from 0 to cols-1:
     - Start at position (0, col)
     - Move diagonally: (i, j) → (i+1, j+1)
     - Continue while row < rows and col < cols
     - Append characters to result
4. Remove trailing spaces from the result

**Time Complexity:** O(n) where n = len(encodedText), as we visit each character exactly once
**Space Complexity:** O(n) for storing the matrix and result

**Explanation of the provided solution:**
```python
class Solution:
    def decodeCiphertext(self, s: str, rows: int) -> str:
        n = len(s)
        cols = n // rows  # Calculate columns needed
        
        # Reconstruct matrix from encoded text (row-wise)
        mat = []
        for i in range(rows):
            mat.append(s[i * cols : i * cols + cols])
        
        res = []
        
        # Read diagonally starting from each column
        for start_col in range(cols):
            i, j = 0, start_col  # Start at row 0, current column
            
            # Move diagonally down-right
            while i < rows and j < cols:
                res.append(mat[i][j])
                i += 1  # Move down
                j += 1  # Move right
        
        # Remove trailing spaces
        return ''.join(res).rstrip()
```

**How it works:**
- The matrix is reconstructed by treating the encodedText as concatenated rows
- The nested loop reads diagonals: for column 0, we read (0,0)→(1,1)→(2,2)...; for column 1, we read (0,1)→(1,2)→(2,3)... and so on
- This reverse diagonal reading recovers the original placement order of characters
- Finally, trailing spaces are removed since the original text doesn't have them

# Tags
- Matrix Construction
- Diagonal Traversal
- String Encoding/Decoding
- Transposition Cipher

