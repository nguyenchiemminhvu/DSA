## Problem

https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/description

Given 3 positive numbers `a`, `b`, and `c`, return the **minimum number of flips** required in some bits of `a` and `b` to make `(a OR b == c)`.

A flip operation consists of changing any single bit from 1 to 0 or from 0 to 1 in the binary representation.

### Examples

**Example 1:**
- Input: `a = 2, b = 6, c = 5`
- Output: `3`
- Explanation: After flips `a = 1`, `b = 4`, `c = 5` such that `(a OR b == c)` which is `(1 OR 4 == 5)`

**Example 2:**
- Input: `a = 4, b = 2, c = 7`
- Output: `1`

**Example 3:**
- Input: `a = 1, b = 2, c = 3`
- Output: `0`

### Constraints

- $1 \leq a, b, c \leq 10^9$

## Observations

1. **Bit-by-bit approach**: We can process the problem bit by bit from the least significant bit (LSB) to the most significant bit (MSB). Each bit position is independent in terms of the OR operation.

2. **OR operation behavior**:
   - `0 OR 0 = 0`
   - `0 OR 1 = 1`
   - `1 OR 0 = 1`
   - `1 OR 1 = 1`

3. **Case analysis at each bit position**:
   - If the target bit in `c` is `0`: Both bits in `a` and `b` must be `0`. Count flips needed.
   - If the target bit in `c` is `1`: At least one bit in `a` or `b` must be `1`. Count flips needed.

4. **No need to consider higher bits**: Once all original bits are processed, the loop terminates naturally. Bits that don't exist (beyond the number's representation) are considered as `0`.

5. **Greedy nature**: The solution processes each bit independently. The minimum flips for one bit position doesn't affect other positions, making a greedy bit-by-bit approach optimal.

## Solution

### Algorithm

Process both numbers `a` and `b` bit by bit from right to left:

1. Extract the least significant bit (LSB) of each number: `a & 1`, `b & 1`, `c & 1`
2. Analyze based on the target bit in `c`:
   - **If `bit_c == 0`**: The result of `a OR b` must be `0`, so both bits must be `0`.
     - Count flips: `bit_a + bit_b` (flip both if they're `1`)
   - **If `bit_c == 1`**: The result of `a OR b` must be `1`, so at least one bit must be `1`.
     - If both bits are `0`: Need 1 flip
     - If at least one bit is `1`: Need 0 flips
     - Count flips: `(bit_a | bit_b) ^ 1` (flip only if `OR` result is `0`)
3. Right shift all numbers by 1 bit: `a >>= 1`, `b >>= 1`, `c >>= 1`
4. Continue until all numbers become `0`

### Code Implementation

```python
class Solution:
    def minFlips(self, a: int, b: int, c: int) -> int:
        flips = 0
        while a or b or c:
            # Extract the least significant bits
            bit_a = a & 1
            bit_b = b & 1
            bit_c = c & 1
            
            if bit_c == 0:
                # Target bit is 0: both a and b must be 0
                # Count how many bits need to flip (1 -> 0)
                flips += (bit_a + bit_b)
            else:
                # Target bit is 1: at least one of a or b must be 1
                # If both are 0, need 1 flip; otherwise, need 0 flips
                # (bit_a | bit_b) gives 1 if at least one is 1, 0 if both are 0
                # ^ 1 flips this result, so we get 0 if at least one is 1, 1 if both are 0
                flips += (bit_a | bit_b) ^ 1
            
            # Process the next bit
            a >>= 1
            b >>= 1
            c >>= 1
        
        return flips
```

### Complexity Analysis

- **Time Complexity**: $O(\log \max(a, b, c))$ or $O(32)$ in practice
  - We process each bit of the numbers. The maximum number has at most 30 bits (since $10^9 < 2^{30}$)
  - The loop runs until all numbers become 0, which happens in $O(\log n)$ iterations where $n$ is the maximum value

- **Space Complexity**: $O(1)$
  - We only use a constant amount of extra space for variables

### Walkthrough Example

**Example 1:** `a = 2, b = 6, c = 5`

Binary representations:
- `a = 2` → `010`
- `b = 6` → `110`
- `c = 5` → `101`

Step-by-step bit processing:

| Iteration | bit_a | bit_b | bit_c | Operation | Flips | a | b | c |
|-----------|-------|-------|-------|-----------|-------|---|---|---|
| Initial   | - | - | - | - | 0 | 010 | 110 | 101 |
| 1 | 0 | 0 | 1 | `(0\|0)^1=1` | 1 | 001 | 011 | 010 |
| 2 | 1 | 1 | 0 | `1+1=2` | 3 | 000 | 001 | 001 |
| 3 | 0 | 1 | 1 | `(0\|1)^1=0` | 3 | 000 | 000 | 000 |

**Result**: 3 flips needed

### Edge Cases

1. If `a | b == c` already, return `0` (no flips needed)
2. If `c` is larger than `a | b`, we need to flip bits in `a` or `b` to make them `1`
3. If `c` has some bits set to `0` where `a | b` has bits set to `1`, we need flips

# Tags

#bit-manipulation #greedy #leetcode

