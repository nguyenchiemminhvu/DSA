## Problem

https://leetcode.com/problems/power-of-four/

```
Given an integer n, return true if it is a power of four. Otherwise, return false.

An integer n is a power of four, if there exists an integer x such that n == 4x.

Example 1:

Input: n = 16
Output: true

Example 2:

Input: n = 5
Output: false

Example 3:

Input: n = 1
Output: true

Constraints:

-231 <= n <= 231 - 1

Follow up: Could you solve it without loops/recursion?
```

## Observations

1. **Powers of 4 Pattern**: Powers of `4` are: `1, 4, 16, 64, 256, 1024, ...`
   - In binary: `1 (1), 100 (4), 10000 (16), 1000000 (64), 100000000 (256), ...`
   - All powers of 4 have exactly one bit set (they are powers of `2`)
   - The single bit is always at an even position (0-indexed from right): positions `0, 2, 4, 6, 8, ...`

2. **Key Insights**:
   - A power of `4` must first be a power of `2` (only one bit set)
   - Among powers of `2`, only those with the bit at even positions are powers of `4`
   - Powers of `2` at odd positions `(2, 8, 32, 128, ...)` are NOT powers of `4`

3. **Bit Manipulation Approach**:
   - Use `n & (n-1) == 0` to check if `n` is a power of `2`
   - Use a bitmask to check if the single bit is at an even position
   - The mask `0x55555555` has bits set at all even positions: `01010101010101010101010101010101`

4. **Edge Cases**:
   - `n ≤ 0` are not powers of `4`
   - `n = 1 = 4^0` is a power of `4`

## Solution

1. **Power of 2 Check**: `n & (n - 1) != 0`
   - For any power of 2, `n & (n-1)` equals `0`
   - Example: `16 (10000) & 15 (01111) = 0`
   - If this condition fails, n is not even a power of 2, so return False

2. **Even Position Check**: `n & 0x55555555 > 0`
   - `0x55555555` = `01010101010101010101010101010101` (binary)
   - This mask has 1s at all even bit positions `(0, 2, 4, 6, ...)`
   - If n is a power of `4`, its single bit will be at an even position
   - The AND operation will be > 0 only if the bit is at an even position

**Examples:**
```
- n = 16 (10000₂): Position 4 (even) → 16 & 0x55555555 = 16 > 0 ✓
- n = 8 (1000₂): Position 3 (odd) → 8 & 0x55555555 = 0 ✗
- n = 1 (1₂): Position 0 (even) → 1 & 0x55555555 = 1 > 0 ✓
```

**Time Complexity**: `O(1)` - constant time bit operations
**Space Complexity**: `O(1)` - only using constant extra space

**Alternative Understanding of the Mask:**
- Powers of `4` in binary: `1, 100, 10000, 1000000, ...`
- All have the pattern where the single '1' bit is at positions: `0, 2, 4, 6, 8, ...`
- The mask `0x55555555` captures exactly these positions

## Tags

bit manipulation