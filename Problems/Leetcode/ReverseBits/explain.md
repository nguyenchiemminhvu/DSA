## Problem

https://leetcode.com/problems/reverse-bits/description/

```
Reverse bits of a given 32 bits signed integer.

Example 1:

Input: n = 43261596

Output: 964176192

Explanation:

Integer	Binary
43261596	00000010100101000001111010011100
964176192	00111001011110000010100101000000
Example 2:

Input: n = 2147483644

Output: 1073741822

Explanation:

Integer	Binary
2147483644	01111111111111111111111111111100
1073741822	00111111111111111111111111111110

Constraints:

0 <= n <= 231 - 2
n is even.

Follow up: If this function is called many times, how would you optimize it?
```

## Observations

The problem asks us to reverse the bits of a 32-bit integer. This means the least significant bit (rightmost) becomes the most significant bit (leftmost) and vice versa.

**Key Insights:**
1. **Bit Reversal Pattern**: We need to swap bits at positions (i, 31-i) for all i from 0 to 15
2. **Divide and Conquer Approach**: Instead of swapping individual bits, we can use a more efficient approach by swapping larger chunks progressively
3. **Bit Masking**: We can use bit masks to isolate specific bit groups and then shift them to their new positions
4. **Performance**: The provided solution uses a clever divide-and-conquer technique that reverses bits in O(1) time with exactly 5 operations

**Pattern Analysis:**
- First swap 16-bit halves
- Then swap 8-bit chunks within each 16-bit half  
- Then swap 4-bit chunks within each 8-bit chunk
- Then swap 2-bit chunks within each 4-bit chunk
- Finally swap individual bits within each 2-bit chunk

## Solution

**Approach: Divide and Conquer Bit Manipulation**

The solution uses an elegant divide-and-conquer approach that reverses bits by progressively swapping larger and smaller chunks of bits.

```python
class Solution:
    def reverseBits(self, n: int) -> int:
        n = ((n & 0xFFFF) << 16) | ((n & 0xFFFF0000) >> 16)
        n = ((n & 0x00FF00FF) << 8) | ((n & 0xFF00FF00) >> 8)
        n = ((n & 0x0F0F0F0F) << 4) | ((n & 0xF0F0F0F0) >> 4)
        n = ((n & 0x33333333) << 2) | ((n & 0xCCCCCCCC) >> 2)
        n = ((n & 0x55555555) << 1) | ((n & 0xAAAAAAAA) >> 1)
        return n
```

**Step-by-Step Breakdown:**

1. **Swap 16-bit halves:**
   - `0xFFFF` = `0000000000000000111111111111111` (lower 16 bits)
   - `0xFFFF0000` = `1111111111111111000000000000000` (upper 16 bits)
   - Extract lower 16 bits, shift left by 16 positions
   - Extract upper 16 bits, shift right by 16 positions
   - Combine with OR operation

2. **Swap 8-bit chunks:**
   - `0x00FF00FF` = `00000000111111110000000011111111` (8-bit chunks at positions 0-7, 16-23)
   - `0xFF00FF00` = `11111111000000001111111100000000` (8-bit chunks at positions 8-15, 24-31)
   - Swap 8-bit chunks within each 16-bit half

3. **Swap 4-bit chunks:**
   - `0x0F0F0F0F` = `00001111000011110000111100001111` (4-bit chunks)
   - `0xF0F0F0F0` = `11110000111100001111000011110000` (complementary 4-bit chunks)
   - Swap 4-bit chunks within each 8-bit section

4. **Swap 2-bit chunks:**
   - `0x33333333` = `00110011001100110011001100110011` (2-bit chunks)
   - `0xCCCCCCCC` = `11001100110011001100110011001100` (complementary 2-bit chunks)
   - Swap 2-bit chunks within each 4-bit section

5. **Swap individual bits:**
   - `0x55555555` = `01010101010101010101010101010101` (odd positions)
   - `0xAAAAAAAA` = `10101010101010101010101010101010` (even positions)
   - Swap individual bits within each 2-bit pair

**Example Trace:**
Let's trace through `n = 43261596` (`00000010100101000001111010011100`):

```
Original:     00000010100101000001111010011100

Step 1 (16):  00011110100111000000001010010100
Step 2 (8):   00111001011110000010100101000000  
Step 3 (4):   00111001011110000010100101000000
Step 4 (2):   00111001011110000010100101000000
Step 5 (1):   00111001011110000010100101000000
```

**Time Complexity**: O(1) - exactly 5 bit manipulation operations
**Space Complexity**: O(1) - only using the input variable

**Alternative Approaches:**
1. **Bit-by-bit reversal**: Extract each bit and build result (32 operations)
2. **Lookup table**: Pre-compute all possible reversals (space-intensive but fastest for multiple calls)
3. **Recursive divide-and-conquer**: Similar logic but with function calls (slower due to overhead)

## Tags

bit manipulation