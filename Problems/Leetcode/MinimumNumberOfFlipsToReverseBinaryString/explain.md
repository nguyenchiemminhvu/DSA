## Problem

https://leetcode.com/problems/minimum-number-of-flips-to-reverse-binary-string/

```
You are given a positive integer n.

Let s be the binary representation of n without leading zeros.

The reverse of a binary string s is obtained by writing the characters of s in the opposite order.

You may flip any bit in s (change 0 → 1 or 1 → 0). Each flip affects exactly one bit.

Return the minimum number of flips required to make s equal to the reverse of its original form.

Example 1:

Input: n = 7

Output: 0

Explanation:

The binary representation of 7 is "111". Its reverse is also "111", which is the same. Hence, no flips are needed.

Example 2:

Input: n = 10

Output: 4

Explanation:

The binary representation of 10 is "1010". Its reverse is "0101". All four bits must be flipped to make them equal. Thus, the minimum number of flips required is 4.

Constraints:

1 <= n <= 109
```

## Observations

1. **Problem Analysis**: We need to find the minimum number of bit flips to make a binary string equal to its reverse.

2. **Key Insight**: To make a string equal to its reverse, we need to compare each bit at position `i` with the bit at position `length-1-i`. If they differ, we need to flip one of them.

3. **Optimization**: Instead of flipping bits in the original string, we can:
   - Compute the reverse of the number directly using bit manipulation
   - Use XOR to find positions where bits differ
   - Count the number of differing bits using Brian Kernighan's algorithm

4. **Examples**:
   - n = 7 → binary "111" → reverse "111" → same, so 0 flips needed
   - n = 10 → binary "1010" → reverse "0101" → all bits differ, so 4 flips needed

## Solution

1. **Reverse Computation**: 
   - Extract each bit from right to left using `temp & 1`
   - Build reverse by shifting left and adding the extracted bit
   - Continue until all bits are processed

2. **Difference Detection**:
   - XOR the original number with its reverse: `rev_n ^ n`
   - This gives us a number where set bits indicate positions that differ

3. **Bit Counting**:
   - Use Brian Kernighan's algorithm: `x & (x-1)` removes the rightmost set bit
   - Count how many times we can do this until x becomes 0

**Time Complexity**: O(log n) - proportional to the number of bits in n
**Space Complexity**: O(1) - only using constant extra space

**Example Walkthrough** (n = 10):
- Binary of 10: "1010"
- Reverse: "0101" (which is 5 in decimal)
- XOR: 10 ^ 5 = 1010 ^ 0101 = 1111 (15 in decimal)
- Count bits in 15: 4 set bits → return 4

# Tags
- Bit Manipulation
- Binary String
- XOR Operations
- Brian Kernighan's Algorithm

