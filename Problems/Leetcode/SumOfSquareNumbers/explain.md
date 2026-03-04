## Problem

https://leetcode.com/problems/sum-of-square-numbers/description/

Given a non-negative integer `c`, decide whether there exist two integers `a` and `b` such that `a² + b² = c`.

**Examples:**
- Input: `c = 5` → Output: `true` (1² + 2² = 5)
- Input: `c = 3` → Output: `false`

**Constraints:** `0 <= c <= 2³¹ - 1`

## Observations

- We need to find a pair `(a, b)` with `a >= 0` and `b >= 0` such that `a² + b² = c`.
- WLOG assume `a <= b`. Then `b² <= c`, meaning `b <= sqrt(c)`. So it's sufficient to search `a` in `[0, sqrt(c)]` and `b` in `[0, sqrt(c)]`.
- The search space can be viewed as a 2D grid where rows are values of `a` and columns are values of `b`. The sums `a² + b²` are **monotonically increasing along both axes** — increasing `a` increases the sum, decreasing `b` decreases it.
- This monotone structure allows a **two-pointer approach**: start with the widest possible window (`a = 0`, `b = floor(sqrt(c))`) and converge inward based on whether the current sum is too large or too small.
- Using `int(sqrt(c)) + 1` as the initial right bound is a safe guard against floating-point imprecision in `sqrt`; the first iteration will immediately shrink it if needed.

## Solution

**Two Pointers** — O(√c) time, O(1) space.

Set `left = 0` and `right = floor(sqrt(c))`. At each step compute `s = left² + right²`:
- `s == c` → found a valid pair, return `True`.
- `s > c` → the sum is too large; decrement `right` to reduce it.
- `s < c` → the sum is too small; increment `left` to increase it.

If the pointers cross without finding a match, return `False`.

```python
from math import sqrt

class Solution:
    def judgeSquareSum(self, c: int) -> bool:
        left = 0
        right = int(sqrt(c)) + 1
        while left <= right:
            s = left ** 2 + right ** 2
            if s == c:
                return True
            if s > c:
                right -= 1
            else:
                left += 1
        
        return False
```

**Why it works:** Because we constrain `b <= sqrt(c)`, every valid pair `(a, b)` with `a <= b` lives within the search window. The two-pointer never skips a valid pair: if `s > c` we can safely discard the current `right` (no smaller `left` can compensate, as left only moves right), and if `s < c` we can safely discard the current `left`.

# Tags

`Two Pointers` `Math`

