## Problem

https://leetcode.com/problems/minimum-operations-to-reduce-an-integer-to-0/description

```
You are given a positive integer n. You can do the following operation any number of times:
  - Add or subtract a power of 2 from n.

Return the minimum number of operations to make n equal to 0.

A number x is a power of 2 if x == 2^i where i >= 0.

Example 1:
  Input: n = 39
  Output: 3
  Explanation:
    - Add 2^0 = 1 → n = 40
    - Subtract 2^3 = 8 → n = 32
    - Subtract 2^5 = 32 → n = 0

Example 2:
  Input: n = 54
  Output: 3
  Explanation:
    - Add 2^1 = 2 → n = 56
    - Add 2^3 = 8 → n = 64
    - Subtract 2^6 = 64 → n = 0

Constraints: 1 <= n <= 10^5
```

## Observations

1. **Power of 2 is the base case**: If `n` is already a power of 2, we only need 1 operation (subtract `n` itself).

2. **Binary representation is key**: Each set bit in `n` corresponds to at least one operation. However, we do not have to handle each bit independently — we can *carry* by adding a power of 2 to merge consecutive set bits.

3. **Consecutive 1-bits can be merged cheaply**: A run of consecutive 1-bits like `0b0111` (= 7) can be resolved in 2 operations:
   - Add 1 → `0b1000` (= 8, a power of 2)
   - Subtract 8 → 0
   
   Rather than 3 operations (one per bit). So a contiguous "block" of set bits costs **2 operations** (or **1** if the whole number is a power of 2 after merging).

4. **The lowest set bit (lowbit) drives the choice**: At each step, `lowbit = val & (-val)` isolates the least significant set bit. We have two choices:
   - **Subtract lowbit**: clears the lowest bit, moving "rightward" through the binary representation.
   - **Add lowbit**: triggers a carry that merges the lowest bit with adjacent bits above it, potentially reducing the total number of set bits.
   
   We recurse on both choices and take the minimum.

5. **Memoization avoids redundant work**: Many values are revisited (especially after carries), so caching results in `mem` keeps the solution efficient.

## Solution

```python
class Solution:
    def minOperations(self, n: int) -> int:
        mem = {}
        def F(val: int) -> int:
            # Base case: already zero
            if val == 0:
                return 0
            # val is a power of 2: one subtract finishes it
            if val & (val - 1) == 0:
                return 1
            if val in mem:
                return mem[val]

            # Isolate the lowest set bit
            lowbit = val & (-val)

            # Option 1: subtract lowbit → clears the lowest bit
            # Option 2: add lowbit    → carries into higher bits, merging consecutive 1s
            res = min(1 + F(val - lowbit), 1 + F(val + lowbit))

            mem[val] = res
            return res

        return F(n)
```

**How it works on n = 39 (`0b100111`):**
- `lowbit = 1`
- `F(39 - 1) = F(38)` → leads to path: 38 → 36 → 32 → 0 = 3 ops (total 4)
- `F(39 + 1) = F(40)` → `40 = 0b101000`, lowbit = 8
  - `F(40 - 8) = F(32)` → 32 is a power of 2 = 1 op → F(40) = 2
  - → F(39) = **3** ✓

**Complexity:**
- Time: O(log n) unique states (the values reachable via lowbit operations grow/shrink by powers of 2, so the recursion depth and distinct values are bounded by O(log n)).
- Space: O(log n) for the memo table and call stack.

# Tags
`dynamic-programming` `memoization` `bit-manipulation` `greedy`

