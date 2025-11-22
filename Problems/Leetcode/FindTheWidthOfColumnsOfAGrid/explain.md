## Problem

https://leetcode.com/problems/find-the-width-of-columns-of-a-grid/description/

```
You are given a 0-indexed m x n integer matrix grid. The width of a column is the maximum length of its integers.

For example, if grid = [[-10], [3], [12]], the width of the only column is 3 since -10 is of length 3.
Return an integer array ans of size n where ans[i] is the width of the ith column.

The length of an integer x with len digits is equal to len if x is non-negative, and len + 1 otherwise.

Example 1:

Input: grid = [[1],[22],[333]]
Output: [3]
Explanation: In the 0th column, 333 is of length 3.

Example 2:

Input: grid = [[-15,1,3],[15,7,12],[5,6,-2]]
Output: [3,1,2]
Explanation: 
In the 0th column, only -15 is of length 3.
In the 1st column, all integers are of length 1. 
In the 2nd column, both 12 and -2 are of length 2.

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 100 
-109 <= grid[r][c] <= 109
```

## Observations

1. **Understanding the problem**: We need to find the width (maximum number of characters) of each column in a grid.

2. **Width calculation**: The width of an integer is:
   - For positive numbers: number of digits
   - For negative numbers: number of digits + 1 (for the minus sign)
   - Zero: 1 digit

3. **Key insight**: We can use `len(str(number))` to get the width of any integer, as converting to string automatically handles:
   - Negative numbers (includes the minus sign)
   - Positive numbers (just the digits)
   - Zero (returns "0" with length 1)

4. **Algorithm approach**: 
   - Initialize result array with 1s (minimum width)
   - For each column, iterate through all rows
   - Track the maximum width found in each column

## Solution

1. **Initialize dimensions**: Get `m` (rows) and `n` (columns) from the grid.

2. **Initialize result**: Create `res` array with `n` elements, all set to 1 (minimum possible width).

3. **Column-wise iteration**: For each column `c` from 0 to `n-1`:
   - Iterate through each row in the grid
   - Calculate width of current element using `len(str(row[c]))`
   - Update `res[c]` with the maximum width seen so far for this column

4. **Return result**: The `res` array contains the maximum width for each column.

**Time Complexity**: O(m × n) where m is rows and n is columns
**Space Complexity**: O(n) for the result array

**Example walkthrough** with `grid = [[-15,1,3],[15,7,12],[5,6,-2]]`:
- Column 0: max(len("-15"), len("15"), len("5")) = max(3, 2, 1) = 3
- Column 1: max(len("1"), len("7"), len("6")) = max(1, 1, 1) = 1  
- Column 2: max(len("3"), len("12"), len("-2")) = max(1, 2, 2) = 2
- Result: [3, 1, 2]

# Tags

array, string