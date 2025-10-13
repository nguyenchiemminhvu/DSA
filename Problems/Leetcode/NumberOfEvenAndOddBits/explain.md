## Problem

https://leetcode.com/problems/number-of-even-and-odd-bits/description/

```
You are given a positive integer n.

Let even denote the number of even indices in the binary representation of n with value 1.

Let odd denote the number of odd indices in the binary representation of n with value 1.

Note that bits are indexed from right to left in the binary representation of a number.

Return the array [even, odd].

Example 1:

Input: n = 50

Output: [1,2]

Explanation:

The binary representation of 50 is 110010.

It contains 1 on indices 1, 4, and 5.

Example 2:

Input: n = 2

Output: [0,1]

Explanation:

The binary representation of 2 is 10.

It contains 1 only on index 1.

Constraints:

1 <= n <= 1000
```

## Observations

1. **Index Definition**: Indices are counted from right to left (LSB to MSB), starting at index 0
   - Index 0, 2, 4, 6... are **even** indices
   - Index 1, 3, 5, 7... are **odd** indices

2. **Example Analysis** (n = 50):
   ```
   Binary: 110010
   Index:  543210
   
   Position 1: 1 (odd index)  ✓
   Position 4: 1 (even index) ✓
   Position 5: 1 (odd index)  ✓
   
   Result: [even=1, odd=2]
   ```

3. **Key Insight**: We need to:
   - Iterate through each bit position from right to left
   - Track whether current position is even or odd
   - Count bits with value 1 at even and odd positions separately

4. **Bit Manipulation Approach**:
   - Use `n & 1` to check the rightmost bit
   - Use `n >>= 1` to shift right and process the next bit
   - Alternate between even/odd index tracking

## Solution

### Approach: Bit-by-Bit Processing with Alternating Index

**Algorithm**:
1. Initialize `idx = 0` to track current position parity (0 for even, 1 for odd)
2. Initialize `counter = [0, 0]` where:
   - `counter[0]` stores count of 1s at even indices
   - `counter[1]` stores count of 1s at odd indices
3. Process each bit from right to left:
   - Check if current bit is 1 using `n & 1`
   - Add result to `counter[idx]` (increments by 1 if bit is 1, by 0 otherwise)
   - Toggle index: `idx = (idx + 1) % 2` (0→1→0→1...)
   - Shift right: `n >>= 1`
4. Return `counter` array

**Why This Works**:
- Starting with `idx = 0` corresponds to the rightmost bit being at index 0 (even)
- Each iteration processes one bit and moves to the next position
- The alternating `idx` naturally tracks even/odd positions
- `counter[idx] += (n & 1)` elegantly adds 1 only when the bit is set

**Time Complexity**: O(log n) - processes each bit once (max ~10 bits for n ≤ 1000)

**Space Complexity**: O(1) - only uses fixed-size counter array

**Example Walkthrough** (n = 50 = 110010₂):

```
Iteration | n (binary) | idx | n & 1 | counter     | n after shift
----------|------------|-----|-------|-------------|--------------
Start     | 110010     | 0   |   -   | [0, 0]      | -
1         | 110010     | 0   |   0   | [0, 0]      | 11001
2         | 11001      | 1   |   1   | [0, 1]      | 1100
3         | 1100       | 0   |   0   | [0, 1]      | 110
4         | 110        | 1   |   0   | [0, 1]      | 11
5         | 11         | 0   |   1   | [1, 1]      | 1
6         | 1          | 1   |   1   | [1, 2]      | 0
Result: [1, 2] ✓
```

## Tags

bit manipulation