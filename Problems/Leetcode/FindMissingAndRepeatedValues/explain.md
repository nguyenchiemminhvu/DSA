## Problem

https://leetcode.com/problems/find-missing-and-repeated-values/description/

```
You are given a 0-indexed 2D integer matrix grid of size n * n with values in the range [1, n2]. Each integer appears exactly once except a which appears twice and b which is missing. The task is to find the repeating and missing numbers a and b.

Return a 0-indexed integer array ans of size 2 where ans[0] equals to a and ans[1] equals to b.

Example 1:

Input: grid = [[1,3],[2,2]]
Output: [2,4]
Explanation: Number 2 is repeated and number 4 is missing so the answer is [2,4].

Example 2:

Input: grid = [[9,1,7],[8,9,2],[3,4,6]]
Output: [9,5]
Explanation: Number 9 is repeated and number 5 is missing so the answer is [9,5].

Constraints:

2 <= n == grid.length == grid[i].length <= 50
1 <= grid[i][j] <= n * n
For all x that 1 <= x <= n * n there is exactly one x that is not equal to any of the grid members.
For all x that 1 <= x <= n * n there is exactly one x that is equal to exactly two of the grid members.
For all x that 1 <= x <= n * n except two of them there is exactly one pair of i, j that 0 <= i, j <= n - 1 and grid[i][j] == x.
```

## Observations

1. **Problem Structure**: We have an n×n grid that should contain numbers from 1 to n² exactly once, but one number appears twice (repeated) and one number is missing.

2. **Mathematical Relationships**: 
   - Let `a` = repeated value, `b` = missing value
   - actual_sum = expected_sum + a - b (we have extra `a` but missing `b`)
   - actual_square_sum = expected_square_sum + a² - b² (same principle with squares)

3. **Key Insight - System of Equations**:
   - We can derive: a - b = sum_diff (difference between actual and expected sums)
   - We can derive: a² - b² = square_sum_diff (difference between actual and expected square sums)
   - Since a² - b² = (a + b)(a - b), we get: a + b = square_sum_diff / sum_diff

4. **Solving the System**:
   - From a - b = sum_diff and a + b = sum_ab
   - Adding: 2a = sum_diff + sum_ab → a = (sum_diff + sum_ab) / 2
   - Subtracting: 2b = sum_ab - sum_diff → b = (sum_ab - sum_diff) / 2

5. **XOR Usage**: The variable `repeated_val` uses XOR but isn't actually used in the final solution. This could be part of an alternative approach or leftover code.

6. **Time Complexity**: O(n²) to traverse the grid once
7. **Space Complexity**: O(1) constant extra space

## Solution

The solution uses a clever mathematical approach based on sum and sum of squares:

### Step 1: Calculate Actual Values
- Traverse the entire grid to calculate:
  - `actual_sum`: sum of all elements in the grid
  - `actual_square_sum`: sum of squares of all elements

### Step 2: Calculate Expected Values
- For a perfect 1 to n² sequence:
  - `expected_sum = n² × (n² + 1) / 2` (sum formula)
  - `expected_square_sum = n² × (n² + 1) × (2×n² + 1) / 6` (sum of squares formula)

### Step 3: Set Up Equations
- Let a = repeated value, b = missing value
- `sum_diff = actual_sum - expected_sum = a - b`
- `square_sum_diff = actual_square_sum - expected_square_sum = a² - b²`

### Step 4: Solve the System
- From a² - b² = (a + b)(a - b), we get:
- `sum_ab = square_sum_diff / sum_diff = a + b`
- Now we have two equations:
  - a - b = sum_diff
  - a + b = sum_ab
- Solving: 
  - `repeated = (sum_diff + sum_ab) / 2`
  - `missing = (sum_ab - sum_diff) / 2`

### Example Walkthrough
For grid = [[1,3],[2,2]]:
- n² = 4, so we expect numbers 1,2,3,4
- actual_sum = 1+3+2+2 = 8
- expected_sum = 4×5/2 = 10
- actual_square_sum = 1+9+4+4 = 18
- expected_square_sum = 4×5×9/6 = 30
- sum_diff = 8-10 = -2 (so a-b = -2)
- square_sum_diff = 18-30 = -12 (so a²-b² = -12)
- sum_ab = -12/(-2) = 6 (so a+b = 6)
- repeated = (-2+6)/2 = 2
- missing = (6-(-2))/2 = 4
- Result: [2,4] ✓

This mathematical approach avoids the need for extra space to track frequencies and solves the problem in a single pass through the grid.

# Tags

math, array, matrix

