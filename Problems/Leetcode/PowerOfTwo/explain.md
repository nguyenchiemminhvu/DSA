## Problem

https://leetcode.com/problems/power-of-two/description/

```
Given an integer n, return true if it is a power of two. Otherwise, return false.

An integer n is a power of two, if there exists an integer x such that n == 2x.

Example 1:

Input: n = 1
Output: true
Explanation: 20 = 1

Example 2:

Input: n = 16
Output: true
Explanation: 24 = 16

Example 3:

Input: n = 3
Output: false

Constraints:

-2^31 <= n <= 2^31 - 1

Follow up: Could you solve it without loops/recursion?
```

## Observations

1. **Powers of two in binary representation**: Any power of two has exactly one bit set in its binary representation:
   - 1 (2^0) = `0001`
   - 2 (2^1) = `0010`
   - 4 (2^2) = `0100`
   - 8 (2^3) = `1000`
   - 16 (2^4) = `10000`

2. **Key insight**: For any power of two `n`, the number `n-1` will have all bits set to 1 up to the position where `n` has its single bit:
   - 8 = `1000`, 7 = `0111`
   - 16 = `10000`, 15 = `01111`
   - 4 = `0100`, 3 = `0011`

3. **Bit manipulation property**: If `n` is a power of two, then `n & (n-1)` will always equal 0, because:
   - `n` has exactly one bit set
   - `n-1` has all lower bits set but the bit that was set in `n` is now 0
   - The AND operation results in 0

4. **Edge cases**:
   - `n = 0` is not a power of two
   - Negative numbers cannot be powers of two
   - `n = 1` is 2^0, so it's a valid power of two

## Solution

```python
class Solution:
    def isPowerOfTwo(self, n: int) -> bool:
        return (n != 0) and ((n & (n - 1)) == 0)
```

**Explanation:**

This solution uses a clever bit manipulation trick that works in O(1) time and O(1) space.

**How it works:**

1. **First condition: `n != 0`**
   - Ensures we handle the edge case where n is 0
   - 0 is not a power of two

2. **Second condition: `(n & (n - 1)) == 0`**
   - This is the core of the algorithm
   - For any power of two, this expression will be 0
   - For non-powers of two, this expression will be non-zero

**Step-by-step examples:**

- **n = 8 (power of two)**:
  - Binary: `1000`
  - n - 1 = 7, Binary: `0111`
  - 8 & 7 = `1000 & 0111 = 0000 = 0` ✓

- **n = 6 (not power of two)**:
  - Binary: `0110`
  - n - 1 = 5, Binary: `0101`
  - 6 & 5 = `0110 & 0101 = 0100 = 4` ≠ 0 ✗

- **n = 1 (power of two, 2^0)**:
  - Binary: `0001`
  - n - 1 = 0, Binary: `0000`
  - 1 & 0 = `0001 & 0000 = 0000 = 0` ✓

**Why this works:**
- Powers of two have exactly one bit set in their binary representation
- Subtracting 1 from a power of two flips all the bits from the rightmost set bit to the least significant bit
- The AND operation between these two numbers will always result in 0 for powers of two
- For non-powers of two (which have multiple bits set), the AND operation will not result in 0

**Time Complexity:** O(1) - Single bitwise operation
**Space Complexity:** O(1) - No extra space needed

## Tags

bit manipulation