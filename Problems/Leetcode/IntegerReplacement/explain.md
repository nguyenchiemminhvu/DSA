## Problem

https://leetcode.com/problems/integer-replacement/description/

```
Given a positive integer n, you can apply one of the following operations:

If n is even, replace n with n / 2.
If n is odd, replace n with either n + 1 or n - 1.
Return the minimum number of operations needed for n to become 1.

Example 1:

Input: n = 8
Output: 3
Explanation: 8 -> 4 -> 2 -> 1

Example 2:

Input: n = 7
Output: 4
Explanation: 7 -> 8 -> 4 -> 2 -> 1
or 7 -> 6 -> 3 -> 2 -> 1
Example 3:

Input: n = 4
Output: 2

Constraints:

1 <= n <= 231 - 1
```

## Observations

1. **Goal**: Transform any positive integer `n` to 1 using minimum operations
2. **Operations available**:
   - If `n` is even: divide by 2 (or right shift by 1 bit)
   - If `n` is odd: either add 1 or subtract 1

3. **Key insight**: When `n` is odd, we need to decide between `n+1` and `n-1`
   - Both operations make the number even, so we can divide by 2 next
   - The optimal choice depends on which path leads to fewer total operations

4. **Bit manipulation perspective**:
   - Dividing by 2 = right shift (`n >> 1`)
   - Adding/subtracting 1 changes the least significant bit pattern
   - We want to minimize the number of 1-bits in the binary representation over time

5. **Pattern analysis for odd numbers**:
   - If `n` ends in binary `...01` (last two bits are `01`), subtracting 1 gives `...00`
   - If `n` ends in binary `...11` (last two bits are `11`), adding 1 gives `...00` (with carry)
   - The `...11` case benefits more from adding 1 because it eliminates multiple consecutive 1-bits

6. **Special case**: When `n = 3` (binary `11`), subtracting 1 gives 2, which is better than adding 1 to get 4

## Solution

1. **Even numbers**: Always divide by 2 (right shift) - no choice needed
2. **Odd numbers**: Choose based on bit pattern:
   - If `n > 3` and last two bits are `11`: add 1
   - Otherwise: subtract 1
   - Special handling for `n = 3`: subtract 1 (3→2→1 is better than 3→4→2→1)

**Why this strategy works**:
- When last two bits are `11`, adding 1 creates a carry that eliminates multiple consecutive 1-bits
- Example: `15` (binary `1111`) → add 1 → `16` (binary `10000`) → much faster to reduce
- When last two bits are `01`, subtracting 1 simply removes the last 1-bit

**Time Complexity**: O(log n) - each operation roughly halves the number
**Space Complexity**: O(1) - only using constant extra space

**Example walkthrough**:
- `n = 7` (binary `111`): 7→8→4→2→1 (4 steps)
- `n = 15` (binary `1111`): 15→16→8→4→2→1 (5 steps)

## Tags

bit manipulation