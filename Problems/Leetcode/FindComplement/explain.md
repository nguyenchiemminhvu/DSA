## Problem

https://leetcode.com/problems/number-complement/

```
The complement of an integer is the integer you get when you flip all the 0's to 1's and all the 1's to 0's in its binary representation.

For example, The integer 5 is "101" in binary and its complement is "010" which is the integer 2.
Given an integer num, return its complement.

Example 1:

Input: num = 5
Output: 2
Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.

Example 2:

Input: num = 1
Output: 0
Explanation: The binary representation of 1 is 1 (no leading zero bits), and its complement is 0. So you need to output 0.

Constraints:

1 <= num < 231
```

## Observations

1. **Key Challenge**: The complement should only flip bits in the actual binary representation, not including leading zeros. For example:
   - Number 5 = `101` (3 bits), complement = `010` = 2
   - NOT `11111111111111111111111111111010` (which would be ~5 in most languages)

2. **Bit Manipulation Approach**: We need to create a mask that has 1s only in positions where the original number has significant bits.

3. **Mask Creation Strategy**: The solution uses a clever technique to create a mask with all 1s up to the highest bit position of the original number.

4. **XOR Operation**: Once we have the correct mask, XOR with the original number flips only the relevant bits.

## Solution

**Step 1: Initialize mask**
```python
mask = num
```
Start with the original number as our mask.

**Step 2: Create a mask with all 1s up to the highest bit**
```python
mask |= (mask >> 1)
mask |= (mask >> 2)
mask |= (mask >> 4)
mask |= (mask >> 8)
mask |= (mask >> 16)
```

This technique progressively fills all bits to the right of the highest set bit with 1s:

Example with num = 5 (binary: `101`):
- Initial: `mask = 101`
- `mask |= (mask >> 1)`: `101 | 010 = 111`
- `mask |= (mask >> 2)`: `111 | 001 = 111`
- Remaining operations don't change it since all relevant bits are already 1

Example with num = 10 (binary: `1010`):
- Initial: `mask = 1010`
- `mask |= (mask >> 1)`: `1010 | 0101 = 1111`
- Remaining operations keep it as `1111`

**Step 3: XOR to get complement**
```python
return num ^ mask
```
XOR the original number with the mask to flip all relevant bits.

### Why This Works:

1. **Mask Generation**: The right-shift and OR operations ensure that all bits from the highest set bit down to bit 0 become 1.

2. **Sufficient Iterations**: Since the constraint is `num < 2^31`, we need at most 31 bits. The sequence 1, 2, 4, 8, 16 covers log₂(31) ≈ 5 iterations, which is sufficient to fill any 32-bit number.

3. **XOR Magic**: When we XOR the original number with this mask:
   - Bits that were 1 become 0 (1 ⊕ 1 = 0)
   - Bits that were 0 become 1 (0 ⊕ 1 = 1)
   - Only the significant bits are affected

### Example Walkthrough:

For num = 5 (`101`):
1. `mask = 101`
2. After all operations: `mask = 111`
3. `5 ^ 7 = 101 ^ 111 = 010 = 2` ✓

### Time & Space Complexity:
- **Time**: O(1) - Fixed number of operations
- **Space**: O(1) - Only using a few variables

### Alternative Approaches:
1. **Bit Length Method**: `(1 << num.bit_length()) - 1 ^ num`
2. **Loop Method**: Find highest bit position, create mask, then XOR

## Tags

bit manipulation