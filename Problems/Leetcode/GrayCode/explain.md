## Problem

https://leetcode.com/problems/gray-code/description/

An **n-bit gray code sequence** is a sequence of 2^n integers where:

- Every integer is in the inclusive range [0, 2^n - 1]
- The first integer is 0
- An integer appears no more than once in the sequence
- The binary representation of every pair of adjacent integers differs by exactly one bit
- The binary representation of the first and last integers differs by exactly one bit

Given an integer `n`, return any valid n-bit gray code sequence.

**Example 1:**
```
Input: n = 2
Output: [0,1,3,2]
Explanation:
The binary representation of [0,1,3,2] is [00,01,11,10].
- 00 and 01 differ by one bit
- 01 and 11 differ by one bit
- 11 and 10 differ by one bit
- 10 and 00 differ by one bit
```

**Example 2:**
```
Input: n = 1
Output: [0,1]
```

**Constraints:**
- 1 <= n <= 16

## Observations

1. **Gray Code Properties**: A Gray code sequence has the unique property that consecutive numbers differ by exactly one bit. This is also known as "reflected binary code."

2. **Direct Formula**: There's a mathematical formula to convert any binary number to its Gray code equivalent: `gray = i ^ (i >> 1)` where `i` is the binary number.

3. **Pattern Recognition**: For n-bit Gray code:
   - We need exactly 2^n numbers
   - Numbers range from 0 to 2^n - 1
   - The sequence naturally satisfies all constraints when using the formula

4. **Bitwise Operation**: The formula works by XORing each bit with the bit to its left:
   - For binary number `i`, we right-shift by 1 to get the left-neighbor bits
   - XOR operation ensures only one bit changes between consecutive Gray codes

5. **Why This Works**: 
   - Binary: ...b3 b2 b1 b0
   - Gray code: ...b3 (b3⊕b2) (b2⊕b1) (b1⊕b0)
   - This construction guarantees single-bit differences

## Solution

### Approach: Direct Conversion Formula

**Algorithm:**
1. Iterate through all numbers from 0 to 2^n - 1
2. For each number `i`, compute its Gray code using: `i ^ (i >> 1)`
3. Append the result to the answer array

**Why the formula works:**

The Gray code of a number can be computed by XORing the number with itself right-shifted by one position:
- This effectively XORs each bit with its left neighbor
- The MSB remains unchanged (XOR with 0)
- All other bits become XOR of two adjacent bits

**Example walkthrough for n=2:**

```
i=0: 00 ^ (00 >> 1) = 00 ^ 00 = 00 = 0
i=1: 01 ^ (01 >> 1) = 01 ^ 00 = 01 = 1  
i=2: 10 ^ (10 >> 1) = 10 ^ 01 = 11 = 3
i=3: 11 ^ (11 >> 1) = 11 ^ 01 = 10 = 2

Result: [0, 1, 3, 2]

Verification:
0 (00) → 1 (01): differ in bit 0 ✓
1 (01) → 3 (11): differ in bit 1 ✓
3 (11) → 2 (10): differ in bit 0 ✓
2 (10) → 0 (00): differ in bit 1 ✓ (circular)
```

**Code:**
```python
class Solution:
    def grayCode(self, n: int) -> List[int]:
        arr = []
        for i in range(1 << n):  # 1 << n = 2^n
            arr.append(i ^ (i >> 1))  # Gray code formula
        return arr
```

**Complexity Analysis:**
- **Time Complexity**: O(2^n) - We iterate through 2^n numbers
- **Space Complexity**: O(2^n) - For storing the result array (not counting output space, O(1))

## Tags

`Math` `Bit Manipulation` `Backtracking`

