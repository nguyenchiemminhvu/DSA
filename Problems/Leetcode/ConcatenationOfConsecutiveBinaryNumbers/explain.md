## Problem

https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/description/

Given an integer `n`, return the decimal value of the binary string formed by concatenating the binary representations of `1` to `n` in order, modulo `10^9 + 7`.

**Example 1:**
- Input: `n = 1` → Output: `1`
- `"1"` in binary = 1

**Example 2:**
- Input: `n = 3` → Output: `27`
- Binary: `"1"` + `"10"` + `"11"` = `"11011"` = 27

**Example 3:**
- Input: `n = 12` → Output: `505379714`

**Constraints:** `1 <= n <= 10^5`

## Observations

1. **Concatenation as arithmetic**: Appending the binary representation of `k` to an existing binary string is equivalent to left-shifting the existing value by the bit-length of `k`, then adding `k`.
   - E.g. appending `"11"` (3) to `"10"` (2): `2 << 2 + 3 = 8 + 3 = 11` = `"1011"` ✓

2. **Recurrence relation**: Let `F(n)` = decimal value of the concatenated string `1..n`. Then:
   $$F(n) = \bigl(F(n-1) \ll \text{bit\_len}(n)\bigr) + n$$
   with base case `F(0) = 0`.

3. **Bit length**: The number of bits needed to represent `k` is $\lfloor \log_2 k \rfloor + 1$, which can be computed by counting right-shifts until the value reaches 0.

4. **Modulo at each step**: Since values grow exponentially, we apply `% (10^9 + 7)` at every recursive step. The left-shift before adding `n` is applied to the already-reduced value, which is valid because:
   $$(a \cdot 2^b + c) \bmod m = \bigl((a \bmod m) \cdot 2^b + c\bigr) \bmod m$$

## Solution

```python
class Solution:
    def concatenatedBinary(self, n: int) -> int:
        MOD = 10**9 + 7

        def count_bit(val: int) -> int:
            # Count the number of bits in val by right-shifting until 0
            count = 0
            while val:
                val >>= 1
                count += 1
            return count

        # Recurrence: F(n) = (F(n-1) << bit_len(n) + n) % MOD
        def F(n: int) -> int:
            if n == 0:
                return 0
            return ((F(n - 1) << count_bit(n)) + n) % MOD

        return F(n)
```

**Step-by-step for n = 3:**

| Step | Action | Value |
|------|--------|-------|
| F(1) | `(F(0) << 1) + 1 = (0 << 1) + 1` | `1` → `"1"` |
| F(2) | `(F(1) << 2) + 2 = (1 << 2) + 2 = 4 + 2` | `6` → `"110"` |
| F(3) | `(F(2) << 2) + 3 = (6 << 2) + 3 = 24 + 3` | `27` → `"11011"` |

**Complexity:**
- Time: O(n log n) — for each of the n numbers, `count_bit` runs in O(log k) time.
- Space: O(n) — recursion call stack depth of n.

> **Note:** For `n = 10^5`, Python's default recursion limit (~1000) will cause a `RecursionError`. In practice, convert `F` to an iterative loop or increase the limit with `sys.setrecursionlimit`.

# Tags

`bit-manipulation` `math` `recursion`

