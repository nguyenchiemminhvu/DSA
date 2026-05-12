## Problem

https://leetcode.com/problems/bitwise-and-of-numbers-range/description

# Bitwise AND of Numbers Range

## Problem

https://leetcode.com/problems/bitwise-and-of-numbers-range/description

Given two integers `left` and `right` that represent the range `[left, right]`, return the bitwise AND of all numbers in this range, inclusive.

### Examples:

**Example 1:**
- Input: `left = 5, right = 7`
- Output: `4`
- Explanation: 5 & 6 & 7 = 4 (binary: 101 & 110 & 111 = 100)

**Example 2:**
- Input: `left = 0, right = 0`
- Output: `0`

**Example 3:**
- Input: `left = 1, right = 2147483647`
- Output: `0`

### Constraints:
- $0 \leq \text{left} \leq \text{right} \leq 2^{31} - 1$

---

## Observations

### Key Insight: Finding the Common Prefix

The crucial observation is that we don't need to compute the AND of every single number in the range. Instead, we need to find the **common bit prefix** between `left` and `right`.

#### Why This Works:

1. **Bit-by-bit Analysis**: When we AND consecutive numbers, the lower bits will eventually become 0 due to the alternating nature of binary representations.

2. **Example with left=5, right=7**:
   ```
   5 = 101
   6 = 110
   7 = 111
   ```
   - The rightmost bit (bit 0) varies among the three numbers, so it becomes 0 in the AND result.
   - Bit 1 also varies (some have 0, some have 1), so it becomes 0.
   - Bit 2 is constant (all have 1), so it remains 1 in the result.
   - Result: 100 = 4 ✓

3. **Common Prefix Property**: If `left` and `right` have the same bit pattern in the higher-order bits, then all numbers between them will also have that same bit pattern. Only the lower bits that differ between `left` and `right` will have variation and thus become 0.

4. **Finding the Prefix**: We can find the common prefix by right-shifting both `left` and `right` until they become equal. The bits that differ get "normalized", and then we shift back left to restore the original position.

### Why Naive AND Doesn't Work:

Computing `left & (left+1) & (left+2) & ... & right` would be:
- **Inefficient**: When the range is large (like 1 to 2147483647), we'd need 2+ billion operations
- **Time Limit Exceeded**: Would fail on large test cases
- **Memory Intensive**: Potentially need to store intermediate results

### Right Shift Until Equal:

When `left != right`, they differ in at least one bit. By right-shifting both simultaneously, we eliminate the differing lower bits:
- Each right shift removes the rightmost bit
- We count how many shifts we need
- The first bit position where both are equal marks the end of the common prefix
- All bits to the right of this position will be 0 in the final AND

---

## Solution

```python
class Solution:
    def rangeBitwiseAnd(self, left: int, right: int) -> int:
        count_shift = 0
        while left != right:
            left >>= 1      # Right shift left by 1
            right >>= 1     # Right shift right by 1
            count_shift += 1  # Count how many shifts we did
        
        return left << count_shift  # Left shift back to original position
```

### Algorithm Explanation:

**Step 1: Find Common Prefix**
- While `left != right`, keep right-shifting both numbers
- This finds the most significant bits that are identical in both numbers
- These identical bits form the common prefix

**Step 2: Restore Position**
- Once `left == right`, we've found the common prefix
- All lower bits (below the common prefix) will become 0 in the AND of the range
- Left-shift back by `count_shift` positions to restore the original bit positions of the common prefix

### Complexity Analysis:

- **Time Complexity**: $O(\log(\max(\text{left}, \text{right}))) = O(32)$ for 32-bit integers
  - We right-shift at most 32 times (the number of bits in the integer)
  - In the worst case (like 1 and 2147483647), we shift 31 times
  
- **Space Complexity**: $O(1)$
  - Only using a counter variable, no extra data structures

### Walkthrough with Example:

**Input**: `left = 5, right = 7`

```
Initial:  left = 5   (101), right = 7   (111), count_shift = 0

Iteration 1:
  left >>= 1  → left = 2   (010)
  right >>= 1 → right = 3  (011)
  count_shift = 1

Iteration 2:
  left >>= 1  → left = 1   (001)
  right >>= 1 → right = 1  (001)
  count_shift = 2

Loop ends (left == right)

Result:
  left << count_shift = 1 << 2 = 4 (100) ✓
```

**Input**: `left = 0, right = 0`

```
Initial: left = 0, right = 0, count_shift = 0

Loop condition (left != right) is false immediately

Result: 0 << 0 = 0 ✓
```

**Input**: `left = 1, right = 2147483647` (0x7FFFFFFF)

```
Binary:
left  = 00000000000000000000000000000001
right = 01111111111111111111111111111111

These differ starting from bit 30 downward, so we shift 31 times until both equal 0.

Result: 0 << 31 = 0 ✓
```

### Why This Solution is Optimal:

1. **Correct**: Leverages the mathematical property of AND operations
2. **Efficient**: Constant time relative to bit width (32 bits max)
3. **Elegant**: Simple logic that directly targets the problem essence
4. **Scalable**: Works for any integer size without modification

---

## Tags

- Bit Manipulation
- Bitwise AND
- Prefix Matching
- Mathematical Insight
- Time Optimization

## Observations

## Solution

# Tags

