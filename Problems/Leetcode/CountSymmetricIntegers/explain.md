## Problem

https://leetcode.com/problems/count-symmetric-integers/description/

```
You are given two positive integers low and high.

An integer x consisting of 2 * n digits is symmetric if the sum of the first n digits of x is equal to the sum of the last n digits of x. Numbers with an odd number of digits are never symmetric.

Return the number of symmetric integers in the range [low, high].

Example 1:

Input: low = 1, high = 100
Output: 9
Explanation: There are 9 symmetric integers between 1 and 100: 11, 22, 33, 44, 55, 66, 77, 88, and 99.

Example 2:

Input: low = 1200, high = 1230
Output: 4
Explanation: There are 4 symmetric integers between 1200 and 1230: 1203, 1212, 1221, and 1230.

Constraints:

1 <= low <= high <= 104
```

## Observations

1. **Definition of Symmetric Integer**: A number is symmetric if it has an even number of digits and the sum of the first half equals the sum of the second half.

2. **Odd Digit Numbers**: Numbers with odd digits can never be symmetric by definition.

3. **Range Constraint**: Given the constraint `1 <= low <= high <= 10^4`, we only need to handle numbers up to 4 digits maximum.

4. **Brute Force Approach**: Since the range is relatively small (max 10,000 numbers), a brute force approach checking each number is feasible.

5. **Examples Analysis**:
   - For `low = 1, high = 100`: Only 2-digit numbers can be symmetric in this range
     - 11: 1+1 = 1+1 ✓
     - 22: 2+2 = 2+2 ✓
     - ... 99: 9+9 = 9+9 ✓
   - For `low = 1200, high = 1230`: 4-digit numbers
     - 1203: 1+2 = 0+3 ✓ (3 = 3)
     - 1212: 1+2 = 1+2 ✓ (3 = 3)
     - 1221: 1+2 = 2+1 ✓ (3 = 3)
     - 1230: 1+2 = 3+0 ✓ (3 = 3)

## Solution

1. **Iterate through range**: Check every number from `low` to `high` inclusive.

2. **Convert to string**: Convert each number to string to easily access individual digits.

3. **Check even length**: Skip numbers with odd number of digits using bitwise AND (`n & 1`).

4. **Calculate digit sums**: 
   - Split the number into two halves
   - Calculate sum of first half digits (`left`)
   - Calculate sum of second half digits (`right`)

5. **Compare sums**: If `left == right`, increment the count.

6. **Return result**: Return total count of symmetric integers found.

**Time Complexity**: O((high - low + 1) × d) where d is the average number of digits
**Space Complexity**: O(d) for string conversion, where d is the maximum number of digits

**Key Implementation Details**:
- Uses `n & 1` for efficient odd number detection (equivalent to `n % 2 == 1`)
- String indexing allows easy digit access without complex mathematical operations
- Simple loop structure makes the algorithm easy to understand and debug

# Tags

Math, String, Brute Force, Simulation

