````markdown
# Maximum XOR of Two Numbers in an Array

## Problem Statement

https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/

Given an integer array `nums`, return the **maximum result** of `nums[i] XOR nums[j]`, where `0 <= i <= j < n`.

### Constraints

- `1 <= nums.length <= 2 * 10^5`
- `0 <= nums[i] <= 2^31 - 1`

### Examples

**Example 1:**
```
Input: nums = [3,10,5,25,2,8]
Output: 28
Explanation: The maximum result is 5 XOR 25 = 28.
```

**Example 2:**
```
Input: nums = [14,70,53,83,49,91,36,80,92,51,66,70]
Output: 127
```

---

## Observations

**1. XOR is bitwise — decide each bit independently.**

The result of `a XOR b` is determined bit by bit. A bit position in the result is `1` if and only if the two operands differ at that position. To maximize the XOR, we want as many high-order bits as possible to be `1`.

**2. Higher-order bits contribute exponentially more than lower-order bits.**

Bit `k` contributes `2^k` to the result. Therefore, we should greedily try to set the most significant bit (MSB) first, then the next, and so on — a greedy bit-by-bit strategy from MSB to LSB is optimal.

**3. Key lemma: `a XOR b = target` ↔ `a XOR target = b`.**

XOR is its own inverse. So checking whether any pair `(a, b)` achieves `a XOR b = candidate` is equivalent to: for each `a`, check if `a XOR candidate` exists in the set of numbers. This lets us do the reachability check in O(n) using a hash set.

**4. Prefix masking isolates "decided" bits.**

When we are at bit position `i` (deciding whether that bit can be `1`), the bits below `i` haven't been decided yet — they should be treated as irrelevant. We apply a running `mask` that keeps only the bits from MSB down to position `i`. We then store **masked prefixes** of all numbers in a set. This ensures the set-complement check only considers the bits we care about at this step.

**5. `max_xor` carries forward confirmed bits.**

After deciding bit `i`, `max_xor` holds the maximum XOR achievable using only bits from `31` down to `i`. When trying to extend to bit `i-1`, we set `candidate = max_xor | (1 << (i-1))`. If we can confirm this candidate is reachable, `max_xor` is updated to `candidate`; otherwise it stays unchanged (bit `i-1` must be `0` in the answer).

**6. Algorithm overview.**

```
max_xor = 0
mask = 0

for bit from 30 down to 0:
    mask |= (1 << bit)
    prefixes = { num & mask for num in nums }
    candidate = max_xor | (1 << bit)
    if any (candidate ^ prefix) in prefixes:
        max_xor = candidate

return max_xor
```

- **Outer loop:** 31 iterations (bits 30..0, since values ≤ 2^31 − 1)
- **Inner loop:** O(n) per bit
- **Overall time:** O(31 · n) = **O(n)**
- **Space:** O(n) for the prefix set

---

## Step-by-Step Walkthrough (Example 1: nums = [3,10,5,25,2,8])

Numbers in binary (5 bits for clarity):
```
 3 = 00011
10 = 01010
 5 = 00101
25 = 11001
 2 = 00010
 8 = 01000
```

**Bit 4 (value 16):**
- `mask = 10000`, `candidate = 00000 | 10000 = 10000` (16)
- Prefixes (top bit only): `{0, 0, 0, 16, 0, 0}` → `{0, 16}`
- Check: `16 ^ 0 = 16` ∈ set ✓
- `max_xor = 16`

**Bit 3 (value 8):**
- `mask = 11000`, `candidate = 10000 | 01000 = 11000` (24)
- Prefixes: `{00, 08, 00, 24, 00, 08}` → `{0, 8, 24}`
- Check: `24 ^ 0 = 24` ∈ set ✓
- `max_xor = 24`

**Bit 2 (value 4):**
- `mask = 11100`, `candidate = 11000 | 00100 = 11100` (28)
- Prefixes: `{00, 08, 04, 24, 00, 08}` → `{0, 4, 8, 24}`
- Check: `28 ^ 4 = 24` ∈ set ✓  (5 & mask = 4, 25 & mask = 24)
- `max_xor = 28`

**Bit 1 (value 2):**
- `mask = 11110`, `candidate = 11100 | 00010 = 11110` (30)
- Prefixes: `{02, 10, 04, 26, 02, 08}` → `{2, 4, 8, 10, 26}`
- Check: `30 ^ p` for each prefix: `28, 26, 24, 20, 4` — none in set ✗
- `max_xor = 28` (unchanged)

**Bit 0 (value 1):**
- `mask = 11111`, `candidate = 11100 | 00001 = 11101` (29)
- Prefixes: `{3, 10, 5, 25, 2, 8}` → `{2, 3, 5, 8, 10, 25}`
- Check: `29 ^ p` for each: `30, 28, 26, 23, 19, 7` — none in set ✗
- `max_xor = 28` (unchanged)

**Answer: 28** ✓ (5 XOR 25 = `00101` XOR `11001` = `11100` = 28)

---

## Complexity Analysis

| Aspect | Complexity |
|--------|-----------|
| Time | O(32 · n) = O(n) |
| Space | O(n) for the prefix set |

---

## Code Solution

```python
from typing import List

class Solution:
    def findMaximumXOR(self, nums: List[int]) -> int:
        max_xor = 0
        mask = 0

        for i in range(30, -1, -1):
            # Extend mask to include bit i
            mask |= (1 << i)

            # Collect all masked prefixes (only care about bits 30..i)
            prefixes = set()
            for val in nums:
                prefixes.add(val & mask)

            # Greedily try to set bit i to 1
            candidate = max_xor | (1 << i)

            # If any two prefixes XOR to candidate, we can achieve it
            for val in prefixes:
                if candidate ^ val in prefixes:
                    max_xor = candidate
                    break

        return max_xor
```
````
