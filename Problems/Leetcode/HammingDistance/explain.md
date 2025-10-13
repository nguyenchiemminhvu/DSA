## Problem

https://leetcode.com/problems/hamming-distance/

```
The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Given two integers x and y, return the Hamming distance between them.

Example 1:

Input: x = 1, y = 4
Output: 2
Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑
The above arrows point to positions where the corresponding bits are different.

Example 2:

Input: x = 3, y = 1
Output: 1

Constraints:

0 <= x, y <= 231 - 1
```

## Observations

1. **XOR Operation Identifies Differing Bits**
   - The XOR (`^`) operation returns `1` when bits are different and `0` when they're the same
   - After `x ^= y`, the resulting value has `1`s only at positions where the original `x` and `y` differed
   - This transforms the problem from comparing two numbers to counting set bits in one number

2. **Brian Kernighan's Algorithm**
   - The expression `x & (x - 1)` is a classic bit manipulation trick
   - It clears the rightmost set bit in `x`
   - Example: if `x = 12 (1100)`, then `x - 1 = 11 (1011)`, and `x & (x - 1) = 8 (1000)`
   - This allows us to count set bits by repeatedly clearing them until `x` becomes `0`

3. **Time Complexity: O(k)** where k is the number of set bits
   - The while loop runs exactly as many times as there are `1` bits in the XOR result
   - In the worst case, this is O(log(max(x, y))) since we're dealing with 32-bit integers
   - Much more efficient than checking each bit position individually

4. **Space Complexity: O(1)**
   - Only uses a constant amount of extra space (the `count` variable)
   - Modifies `x` in place, no additional data structures needed

## Solution

**How it works with Example 1:**
```
x = 1  (0001)
y = 4  (0100)

After x ^= y:
x = 5  (0101)  ← Two bits are set (positions 0 and 2)

Iteration 1:
x = 5 (0101)
x - 1 = 4 (0100)
x & (x-1) = 4 (0100)  ← Cleared rightmost bit, count = 1

Iteration 2:
x = 4 (0100)
x - 1 = 3 (0011)
x & (x-1) = 0 (0000)  ← Cleared rightmost bit, count = 2

Loop ends, return 2 ✓
```

**Alternative Approaches:**
1. Use Python's built-in `bin(x ^ y).count('1')` - simpler but less educational
2. Check each bit position with `(x >> i) & 1` - O(32) for 32-bit integers
3. Use lookup tables for byte-wise counting - faster for large volumes

**Why This Solution is Elegant:**
- Combines two powerful bit manipulation techniques
- Only iterates through set bits, not all bit positions
- No branching inside the loop (efficient for modern CPUs)
- Demonstrates deep understanding of binary operations

## Tags

bit manipulation