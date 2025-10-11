## Problem

https://leetcode.com/problems/number-of-1-bits/

```
Given a positive integer n, write a function that returns the number of set bits in its binary representation (also known as the Hamming weight).

Example 1:

Input: n = 11

Output: 3

Explanation:

The input binary string 1011 has a total of three set bits.

Example 2:

Input: n = 128

Output: 1

Explanation:

The input binary string 10000000 has a total of one set bit.

Example 3:

Input: n = 2147483645

Output: 30

Explanation:

The input binary string 1111111111111111111111111111101 has a total of thirty set bits.

Constraints:

1 <= n <= 231 - 1

Follow up: If this function is called many times, how would you optimize it?
```

## Observations

1. **Problem Goal**: Count the number of 1 bits in the binary representation of a positive integer
2. **Key Insight**: We need an efficient way to count set bits without checking every bit position
3. **Bit Manipulation Trick**: The expression `n & (n - 1)` removes the rightmost set bit from n
4. **Pattern Recognition**: 
   - For n = 12 (1100): n-1 = 11 (1011), so 1100 & 1011 = 1000
   - For n = 8 (1000): n-1 = 7 (0111), so 1000 & 0111 = 0000
5. **Efficiency**: This approach only loops for the number of set bits, not all bit positions

## Solution

1. **Initialize counter**: Start with `count = 0` to track the number of 1 bits
2. **Loop while n > 0**: Continue until all bits are processed
3. **Key operation**: `n = n & (n - 1)` removes the rightmost set bit in each iteration
4. **Increment counter**: Each iteration means we found one more set bit
5. **Return result**: The count represents the total number of 1 bits

**Why `n & (n - 1)` works:**
- When we subtract 1 from n, all trailing zeros become 1s, and the rightmost 1 becomes 0
- The AND operation with the original number eliminates the rightmost set bit
- Example: n = 12 (1100) → n-1 = 11 (1011) → 1100 & 1011 = 1000

**Time Complexity**: O(k) where k is the number of set bits (at most 32 for 32-bit integers)
**Space Complexity**: O(1) - only using a constant amount of extra space

**Alternative Approaches:**
1. **Naive approach**: Check each bit position using bit shifting - O(32) time
2. **Built-in function**: `bin(n).count('1')` - language specific
3. **Lookup table**: Pre-compute results for smaller chunks - faster for repeated calls

## Tags

bit manipulation