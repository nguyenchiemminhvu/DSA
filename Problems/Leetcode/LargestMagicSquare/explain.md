## Problem

https://leetcode.com/problems/largest-magic-square/description/

A **k × k magic square** is a k × k grid filled with integers such that:
- Every row sum is equal
- Every column sum is equal  
- Both diagonal sums are equal
- All these sums are the same value

**Important notes:**
- The integers in the magic square do not have to be distinct
- Every 1 × 1 grid is trivially a magic square

Given an **m × n** integer grid, return the size (i.e., the side length k) of the **largest magic square** that can be found within this grid.

### Examples

**Example 1:**
```
Input: grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
Output: 3

Explanation: The largest magic square has a size of 3.
Every row sum, column sum, and diagonal sum equals 12.
- Row sums: 5+1+6 = 5+4+3 = 2+7+3 = 12
- Column sums: 5+5+2 = 1+4+7 = 6+3+3 = 12
- Diagonal sums: 5+4+3 = 6+4+2 = 12
```

**Example 2:**
```
Input: grid = [[5,1,3,1],[9,3,3,1],[1,3,3,8]]
Output: 2
```

### Constraints
- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 50`
- `1 <= grid[i][j] <= 10^6`

## Observations

1. **Brute Force Approach is Feasible**: With constraints of m, n ≤ 50, we can check all possible squares of all sizes at all positions.

2. **Search Strategy**: 
   - We need to try all possible square sizes k from 1 to min(m, n)
   - For each size k, try all possible top-left positions (i, j)
   - Maximum k is limited by min(m, n)

3. **Magic Square Validation**:
   - First, calculate the target sum (can use first row as reference)
   - Verify all k row sums equal the target
   - Verify all k column sums equal the target
   - Verify main diagonal sum (top-left to bottom-right) equals target
   - Verify anti-diagonal sum (top-right to bottom-left) equals target

4. **Time Complexity Considerations**:
   - Number of possible squares: O(m × n × min(m,n))
   - Checking each square: O(k²) where k is the square size
   - Overall: O(m × n × k³) where k = min(m,n)
   - With constraints ≤ 50, this is acceptable

5. **Edge Cases**:
   - Minimum answer is always 1 (every 1×1 is a magic square)
   - Single row or single column grid still has answer ≥ 1

## Solution

### Approach: Brute Force with Validation

The solution uses a straightforward brute force approach by trying all possible squares and validating each one.

```python
class Solution:
    def largestMagicSquare(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])

        def check(r: int, c: int, k: int) -> bool:
            # Target sum = sum of first row
            target = sum(grid[r][c:c+k])

            # Check all rows
            for i in range(r, r + k):
                if sum(grid[i][c:c+k]) != target:
                    return False

            # Check all columns
            for j in range(c, c + k):
                col_sum = 0
                for i in range(r, r + k):
                    col_sum += grid[i][j]
                if col_sum != target:
                    return False

            # Check main diagonal
            diag1 = 0
            for i in range(k):
                diag1 += grid[r + i][c + i]
            if diag1 != target:
                return False

            # Check anti-diagonal
            diag2 = 0
            for i in range(k):
                diag2 += grid[r + i][c + k - 1 - i]
            if diag2 != target:
                return False

            return True
        
        res = 0
        for k in range(1, n + 1):
            for i in range(m - k + 1):
                for j in range(n - k + 1):
                    if check(i, j, k):
                        res = max(res, k)
        return res
```

### Algorithm Breakdown

**1. Helper Function `check(r, c, k)`**

This function validates if a k×k square starting at position (r, c) is a magic square:

- **Step 1**: Calculate target sum using the first row
  ```python
  target = sum(grid[r][c:c+k])
  ```

- **Step 2**: Verify all k rows have the same sum
  ```python
  for i in range(r, r + k):
      if sum(grid[i][c:c+k]) != target:
          return False
  ```

- **Step 3**: Verify all k columns have the same sum
  ```python
  for j in range(c, c + k):
      col_sum = sum(grid[i][j] for i in range(r, r + k))
      if col_sum != target:
          return False
  ```

- **Step 4**: Verify main diagonal (↘) has the same sum
  ```python
  diag1 = sum(grid[r + i][c + i] for i in range(k))
  if diag1 != target:
      return False
  ```

- **Step 5**: Verify anti-diagonal (↙) has the same sum
  ```python
  diag2 = sum(grid[r + i][c + k - 1 - i] for i in range(k))
  if diag2 != target:
      return False
  ```

**2. Main Loop - Try All Possible Squares**

```python
res = 0
for k in range(1, n + 1):                    # Try all square sizes
    for i in range(m - k + 1):               # Try all valid row positions
        for j in range(n - k + 1):           # Try all valid column positions
            if check(i, j, k):
                res = max(res, k)
return res
```

- Iterate through sizes k from 1 to n (could also use min(m, n))
- For each size, try all valid top-left corner positions
- Valid positions: (i, j) where i + k ≤ m and j + k ≤ n
- Track maximum k that forms a valid magic square

### Complexity Analysis

**Time Complexity: O(m × n × k³)** where k = min(m, n)
- Three nested loops for positions and sizes: O(m × n × k)
- Each `check` operation: O(k²) - checking k rows, k columns, 2 diagonals
- Total: O(m × n × k) × O(k²) = O(m × n × k³)
- With m, n ≤ 50: approximately 50 × 50 × 50³ = 312,500,000 operations (manageable)

**Space Complexity: O(1)**
- Only using constant extra space for variables
- No additional data structures needed

### Key Insights

1. **Early Termination**: The solution could be optimized by trying larger squares first and returning immediately when found, but the current approach is simpler and sufficient.

2. **Why This Works**: By checking every possible square systematically, we guarantee finding the largest magic square if it exists.

3. **No Optimization Needed**: Given the small constraints (≤ 50), the brute force O(n⁴) solution is acceptable and easier to implement correctly.

4. **Alternative Optimizations** (not implemented but possible):
   - Use prefix sums for O(1) row/column sum queries
   - Start from larger k and work downward (early exit)
   - Cache computed sums to avoid redundant calculations

# Tags

`Array` `Matrix` `Brute Force` `Prefix Sum`

