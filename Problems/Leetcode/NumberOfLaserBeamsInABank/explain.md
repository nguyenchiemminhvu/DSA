## Problem

https://leetcode.com/problems/number-of-laser-beams-in-a-bank/description/

```
Anti-theft security devices are activated inside a bank. You are given a 0-indexed binary string array bank representing the floor plan of the bank, which is an m x n 2D matrix. bank[i] represents the ith row, consisting of '0's and '1's. '0' means the cell is empty, while'1' means the cell has a security device.

There is one laser beam between any two security devices if both conditions are met:

The two devices are located on two different rows: r1 and r2, where r1 < r2.
For each row i where r1 < i < r2, there are no security devices in the ith row.
Laser beams are independent, i.e., one beam does not interfere nor join with another.

Return the total number of laser beams in the bank.

Example 1:

Input: bank = ["011001","000000","010100","001000"]
Output: 8
Explanation: Between each of the following device pairs, there is one beam. In total, there are 8 beams:
 * bank[0][1] -- bank[2][1]
 * bank[0][1] -- bank[2][3]
 * bank[0][2] -- bank[2][1]
 * bank[0][2] -- bank[2][3]
 * bank[0][5] -- bank[2][1]
 * bank[0][5] -- bank[2][3]
 * bank[2][1] -- bank[3][2]
 * bank[2][3] -- bank[3][2]
Note that there is no beam between any device on the 0th row with any on the 3rd row.
This is because the 2nd row contains security devices, which breaks the second condition.

Example 2:

Input: bank = ["000","111","000"]
Output: 0
Explanation: There does not exist two devices located on two different rows.

Constraints:

m == bank.length
n == bank[i].length
1 <= m, n <= 500
bank[i][j] is either '0' or '1'.
```

## Observations

1. **Laser beam conditions**: A beam exists between two security devices only if:
   - They are on different rows (r1 < r2)
   - All rows between them have NO security devices (empty rows)

2. **Key insight**: We only need to consider consecutive non-empty rows. If there's an empty row between two rows with devices, no beams can form between them.

3. **Beam calculation**: Between two rows with devices, the number of beams = (devices in row1) × (devices in row2). This is because each device in the first row can connect to each device in the second row.

4. **Algorithm approach**:
   - Count devices in each row
   - Only consider rows with at least one device
   - For each pair of consecutive non-empty rows, multiply their device counts
   - Sum all such products

5. **Example walkthrough** (`["011001","000000","010100","001000"]`):
   - Row 0: 3 devices, Row 1: 0 devices, Row 2: 2 devices, Row 3: 1 device
   - Consecutive non-empty rows: (0,2) and (2,3)
   - Beams: 3×2 + 2×1 = 6 + 2 = 8

## Solution

The solution uses a two-pass approach:

1. **Count devices per row**: `sum_rows = [row.count('1') for row in bank]`
   - Creates an array where each element represents the number of security devices in that row

2. **Process consecutive non-empty rows**:
   ```python
   prev_row = 0  # Index of the previous row with devices
   for i in range(1, len(sum_rows)):
       if sum_rows[i] > 0:  # Current row has devices
           if i - prev_row > 0:  # There was a previous row with devices
               res += (sum_rows[i] * sum_rows[prev_row])
           prev_row = i  # Update previous row index
   ```

3. **Key logic**:
   - `prev_row` tracks the most recent row index that had devices
   - When we find a row with devices, we calculate beams with the previous non-empty row
   - `sum_rows[i] * sum_rows[prev_row]` gives the total beams between these two rows
   - Update `prev_row` to current row for next iteration

**Time Complexity**: O(m × n) where m = number of rows, n = number of columns (for counting '1's in each row)

**Space Complexity**: O(m) for storing the count of devices per row

**Edge Cases**:
- No devices in any row → return 0
- Only one row with devices → return 0 (need at least 2 rows)
- All consecutive rows are empty → return 0

## Tags

array, string