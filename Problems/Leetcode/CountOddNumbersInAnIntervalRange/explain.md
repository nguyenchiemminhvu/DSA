## Problem

https://leetcode.com/problems/count-odd-numbers-in-an-interval-range/

```
Given two non-negative integers low and high. Return the count of odd numbers between low and high (inclusive).

Example 1:
Input: low = 3, high = 7
Output: 3
Explanation: The odd numbers between 3 and 7 are [3,5,7].

Example 2:
Input: low = 8, high = 10
Output: 1
Explanation: The odd numbers between 8 and 10 are [9].

Constraints:
0 <= low <= high <= 10^9
```

## Observations

1. **Range Size**: The total count of numbers in the range `[low, high]` is `r = high - low + 1`

2. **Odd/Even Distribution Pattern**:
   - In any consecutive sequence of numbers, odd and even numbers alternate
   - If the range has an **even count** of numbers (`r` is even):
     - Exactly half are odd, half are even
     - Example: `[8, 9, 10, 11]` → 2 odds, 2 evens
   
   - If the range has an **odd count** of numbers (`r` is odd):
     - The count depends on whether the endpoints are odd or even
     - If **both endpoints are odd**: `(r // 2) + 1` odd numbers
       - Example: `[3, 4, 5, 6, 7]` → `[3, 5, 7]` = 3 odds (5 numbers total)
     - If **at least one endpoint is even**: `r // 2` odd numbers
       - Example: `[2, 3, 4, 5, 6]` → `[3, 5]` = 2 odds (5 numbers total)
       - Example: `[3, 4, 5, 6, 8]` → `[3, 5]` = 2 odds (5 numbers total)

3. **Bit Manipulation for Odd Check**:
   - `n & 1` returns 1 if `n` is odd, 0 if `n` is even
   - This is faster than modulo operation `n % 2`

## Solution

1. Calculate the range size: `r = high - low + 1`

2. Check if `r` is odd using bit manipulation: `r & 1`
   - If `r` is **even**: Return `r // 2` (exactly half are odd)
   - If `r` is **odd**: 
     - Check if both `low` and `high` are odd: `low & 1 and high & 1`
     - If both are odd: Return `r // 2 + 1`
     - Otherwise: Return `r // 2`

**Time Complexity**: O(1) - Only arithmetic and bitwise operations

**Space Complexity**: O(1) - Only a few variables used

**Examples Walkthrough**:

- `low = 3, high = 7`:
  - `r = 7 - 3 + 1 = 5` (odd)
  - Both 3 and 7 are odd: `3 & 1 = 1`, `7 & 1 = 1`
  - Result: `5 // 2 + 1 = 2 + 1 = 3` ✓

- `low = 8, high = 10`:
  - `r = 10 - 8 + 1 = 3` (odd)
  - 8 is even, 10 is even: `8 & 1 = 0`, `10 & 1 = 0`
  - Result: `3 // 2 + 0 = 1` ✓

# Tags

#math #bit-manipulation #pattern-recognition

