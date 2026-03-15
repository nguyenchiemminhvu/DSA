## Problem

https://leetcode.com/problems/count-commas-in-range/description/

Given an integer `n`, return the **total number of commas** used when writing all integers from `[1, n]` (inclusive) in standard number formatting.

In standard formatting:
- A comma is inserted after every three digits from the right.
- Numbers with fewer than 4 digits contain no commas.

**Constraints:** `1 <= n <= 10^5`

**Examples:**
- `n = 1002` → `3` — only `1000`, `1001`, `1002` have a comma (one each)
- `n = 998`  → `0` — all numbers have fewer than 4 digits

## Observations

1. **Comma threshold:** The first number that requires a comma is `1,000`. Any number less than `1000` contributes 0 commas.

2. **One comma per number (within constraints):** Since `n <= 10^5 = 100,000`, every number that has a comma has exactly **one** comma. The second comma would appear at `1,000,000` (7 digits), which is beyond the constraint.

3. **Counting numbers with a comma:** Numbers in `[1000, n]` each contribute exactly 1 comma. The count of such numbers is `n - 999` (when `n >= 1000`).

4. **Edge case:** If `n < 1000`, no commas exist, so the answer is `0`. This is handled by `max(0, ...)`.

## Solution

The total number of commas equals the count of integers in `[1000, n]`:

$$\text{answer} = \max(0,\ n - 999)$$

Because every integer from `1000` to `n` contributes exactly one comma, and there are `n - 1000 + 1 = n - 999` such integers.

```python
class Solution:
    def countCommas(self, n: int) -> int:
        return max(0, n - 999)
```

**Complexity:** O(1) time, O(1) space.

# Tags

`Math` `Counting`

