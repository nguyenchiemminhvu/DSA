## Problem

https://leetcode.com/problems/magic-squares-in-grid/description/

A **3 x 3 magic square** is a 3 x 3 grid filled with **distinct numbers from 1 to 9** such that:
- Each row has the same sum
- Each column has the same sum
- Both diagonals have the same sum

Given a `row x col` grid of integers, determine how many 3 x 3 magic square subgrids exist within it.

**Note:** While a magic square can only contain numbers from 1 to 9, the input grid may contain numbers up to 15.

### Examples

**Example 1:**
```
Input: grid = [[4,3,8,4],
               [9,5,1,9],
               [2,7,6,2]]
Output: 1

Explanation: 
The subgrid starting at (0,0):
[4,3,8]
[9,5,1]
[2,7,6]
is a magic square (all rows, columns, diagonals sum to 15).
```

**Example 2:**
```
Input: grid = [[8]]
Output: 0

Explanation: Grid is too small to contain a 3x3 subgrid.
```

### Constraints
- `row == grid.length`
- `col == grid[i].length`
- `1 <= row, col <= 10`
- `0 <= grid[i][j] <= 15`

---

## Observations

### 1. **Finite Number of Magic Squares**
There are only **8 unique 3x3 magic squares** using numbers 1-9:
- The sum for each row/column/diagonal must be **15** (since 1+2+...+9 = 45, and 45/3 = 15)
- The center must always be **5** (mathematical property of 3x3 magic squares)
- These 8 squares are rotations and reflections of each other

### 2. **Strict Requirements**
A valid magic square must:
- Contain exactly the numbers **1 through 9** (each appearing once)
- Have all rows sum to 15
- Have all columns sum to 15
- Have both diagonals sum to 15

### 3. **Subgrid Extraction**
For any grid of size `m x n`:
- There are `(m - 2) × (n - 2)` possible 3x3 subgrids
- Each subgrid starts at position `(i, j)` where `0 ≤ i ≤ m-3` and `0 ≤ j ≤ n-3`

### 4. **Efficient Comparison**
Instead of checking all magic square properties for each subgrid:
- Pre-store all 8 valid magic squares
- Compare each subgrid directly against this set
- Use hash-based lookup for O(1) comparison

---

## Solution

### Strategy: Pre-computed Magic Squares with Set Lookup

The solution uses a **lookup table approach** that is both simple and efficient:

1. **Pre-define all 8 magic squares** in a list
2. **Convert to a set** for O(1) lookup
3. **Iterate through all possible 3x3 subgrids** in the input grid
4. **Extract each subgrid** and check if it matches any magic square
5. **Count matches**

### Algorithm Steps

```
1. Create a set of all 8 valid magic squares (as tuples for hashability)

2. Get dimensions m, n of the grid
   - If m < 3 or n < 3, return 0 (no 3x3 subgrids possible)

3. Initialize count = 0

4. For each starting position (i, j):
   - Where i ranges from 0 to m-3
   - Where j ranges from 0 to n-3
   
5. For each position:
   - Extract the 3x3 subgrid starting at (i, j)
   - Convert to tuple format for comparison
   - Check if it exists in the magic_squares_set
   - If yes, increment count

6. Return count
```

### Implementation

```python
class Solution:
    def numMagicSquaresInside(self, grid: List[List[int]]) -> int:
        # All 8 valid 3x3 magic squares using numbers 1-9
        magic_squares = [
            [[8, 1, 6], [3, 5, 7], [4, 9, 2]],
            [[6, 7, 2], [1, 5, 9], [8, 3, 4]],
            [[2, 9, 4], [7, 5, 3], [6, 1, 8]],
            [[4, 3, 8], [9, 5, 1], [2, 7, 6]],
            [[6, 1, 8], [7, 5, 3], [2, 9, 4]],
            [[2, 7, 6], [9, 5, 1], [4, 3, 8]],
            [[4, 9, 2], [3, 5, 7], [8, 1, 6]],
            [[8, 3, 4], [1, 5, 9], [6, 7, 2]],
        ]

        # Convert to set of tuples for O(1) lookup
        magic_squares_set = {
            tuple(tuple(row) for row in square)
            for square in magic_squares
        }

        m = len(grid)
        n = len(grid[0])
        
        # Edge case: grid too small
        if m < 3 or n < 3:
            return 0
        
        count = 0
        # Check all possible 3x3 subgrids
        for i in range(m - 2):
            for j in range(n - 2):
                # Extract 3x3 subgrid starting at (i, j)
                sub = tuple([tuple(row[j:j + 3]) for row in grid[i:i+3]])
                
                # Check if it's a magic square
                if sub in magic_squares_set:
                    count += 1
        
        return count
```

### Why This Works

- **Completeness:** We check all possible 3x3 subgrids
- **Correctness:** We only count subgrids that exactly match valid magic squares
- **Efficiency:** Set lookup is O(1), avoiding repeated validation checks

### Complexity Analysis

**Time Complexity: O(m × n)**
- We iterate through `(m - 2) × (n - 2)` positions: O(m × n)
- For each position:
  - Extracting the 3x3 subgrid: O(9) = O(1)
  - Tuple conversion: O(9) = O(1)
  - Set lookup: O(1)
- Overall: O(m × n × 1) = **O(m × n)**

**Space Complexity: O(1)**
- The `magic_squares_set` contains 8 fixed squares: O(8 × 9) = O(72) = O(1)
- The `sub` tuple uses O(9) = O(1) space
- No additional space scales with input size
- Overall: **O(1)** constant space

### Alternative Approach: Validation-Based Solution

Instead of pre-storing magic squares, we could validate each subgrid:

```python
def isMagicSquare(square):
    # Check if contains exactly 1-9
    flat = [num for row in square for num in row]
    if sorted(flat) != list(range(1, 10)):
        return False
    
    # Check sum = 15 for all rows, columns, and diagonals
    target = 15
    
    # Check rows
    for row in square:
        if sum(row) != target:
            return False
    
    # Check columns
    for col in range(3):
        if sum(square[row][col] for row in range(3)) != target:
            return False
    
    # Check diagonals
    if sum(square[i][i] for i in range(3)) != target:
        return False
    if sum(square[i][2-i] for i in range(3)) != target:
        return False
    
    return True
```

**Comparison:**
- **Validation approach:** O(m × n) time, but with higher constant factor
- **Lookup approach (provided):** O(m × n) time with lower constant factor
- The lookup approach is faster in practice because checking set membership is faster than validating all constraints

### Example Walkthrough

**Input:** `grid = [[4,3,8,4], [9,5,1,9], [2,7,6,2]]`

Grid visualization:
```
[4, 3, 8, 4]
[9, 5, 1, 9]
[2, 7, 6, 2]
```

**Possible 3x3 subgrids:**
- Starting at (0,0): `[[4,3,8], [9,5,1], [2,7,6]]` ✓ **Magic square!**
- Starting at (0,1): `[[3,8,4], [5,1,9], [7,6,2]]` ✗ Not a magic square

**Output:** 1

---

# Tags

Array, Matrix, Hash Table, Enumeration

