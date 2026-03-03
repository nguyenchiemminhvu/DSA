## Problem

https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/description/

````markdown
## Problem

https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/description/

Given two positive integers `n` and `k`, the binary string `Sn` is formed as follows:

- `S1 = "0"`
- `Si = Si-1 + "1" + reverse(invert(Si-1))` for `i > 1`

Where:
- `+` denotes concatenation
- `reverse(x)` returns the reversed string `x`
- `invert(x)` flips all bits in `x` (`0` → `1`, `1` → `0`)

Return the `k`-th bit (1-indexed) in `Sn`.

**Constraints:**
- `1 <= n <= 20`
- `1 <= k <= 2^n - 1`

**Examples:**
```
Input: n = 3, k = 1  →  Output: "0"   (S3 = "0111001")
Input: n = 4, k = 11 →  Output: "1"   (S4 = "011100110110001")
```

## Observations

1. **String length doubles + 1 each step:** `|Sn| = 2^n - 1`. After each iteration, the string grows as: 1 → 3 → 7 → 15 → ...

2. **Structure of each Sn:**
   ```
   Sn = S(n-1) | "1" | reverse(invert(S(n-1)))
        [left half] [middle] [right half]
   ```
   The middle bit (position `2^(n-1)`) is always `"1"`. The left half is the previous string unchanged. The right half is the left half inverted and reversed.

3. **Symmetry between halves:** The right half of `Sn` is the mirror-invert of the left half. So every bit in the right half corresponds to a bit in the left half.

4. **Iterative construction is straightforward for small n:** Since `n <= 20`, the maximum string length is `2^20 - 1 = 1,048,575` (~1M characters). Building the string iteratively is perfectly feasible within time and memory limits.

5. **No need for recursion:** While a recursive descent approach (reducing the problem by half at each step) would give O(n) time, the iterative build-up approach is simple, correct, and fast enough given the constraints.

## Solution

Build the string `s` iteratively starting from `S1 = "0"`. At each step `i` from `2` to `n`:
1. Compute the inversion of the current string.
2. Append `"1"` and the reversed inversion to the current string.

After `n` iterations, return the character at position `k - 1` (0-indexed).

```python
class Solution:
    def findKthBit(self, n: int, k: int) -> str:
        s = "0"
        for _ in range(2, n + 1):
            inv = ''.join('1' if c == '0' else '0' for c in s)
            s = s + "1" + inv[::-1]
        return s[k - 1]
```

**Step-by-step trace for n=3, k=1:**
```
Start:  s = "0"
i=2:    inv = "1",       s = "0" + "1" + "1"     = "011"
i=3:    inv = "100",     s = "011" + "1" + "001"  = "0111001"
Return: s[0] = "0"  ✓
```

**Complexity:**
- **Time:** O(2^n) — we build a string of length `2^n - 1`
- **Space:** O(2^n) — to store the string

# Tags

`String` `Recursion` `Simulation`
````

## Observations

## Solution

# Tags

