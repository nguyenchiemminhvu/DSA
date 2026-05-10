## Problem

https://leetcode.com/problems/domino-and-tromino-tiling/description

You have two tile shapes:
- **Domino**: 2×1 (can be placed horizontally or vertically)
- **Tromino**: L-shaped covering 3 cells (can be rotated in 4 ways)

Given an integer `n`, return the number of ways to tile a **2×n** board such that every cell is covered. Return the answer modulo `10^9 + 7`.

```
Example 1: n = 3 → 5
Example 2: n = 1 → 1
Constraints: 1 <= n <= 1000
```

## Observations

**Small cases (build intuition):**
- `n=1`: only one way — one vertical domino. → `f(1) = 1`
- `n=2`: two ways — two vertical dominoes, or two horizontal dominoes. → `f(2) = 2`
- `n=3`: five ways (enumerable by hand). → `f(3) = 5`

**Deriving the recurrence:**

Think of building the board column by column. At column `i`, consider which tiles "end" exactly at column `i` (no tile extends past it):

1. **Place a vertical domino at column `i`**: the remaining left part is a full 2×(i-1) board → contributes `f(i-1)`
2. **Place two horizontal dominoes spanning columns `i-1..i`**: remaining left part is a full 2×(i-2) board → contributes `f(i-2)`
3. **Place a tromino + filler combinations ending at column `i`**:
   - A tromino can leave one cell uncovered in column `i-1`. That gap must be filled by another tromino reaching back to column `i-2`. Each such combination contributes `f(i-3)` ways, and there are **2 mirror orientations**, so contributes `2*f(i-3)`.

Combining and simplifying (the `f(i-2)` term is subsumed):

$$f(i) = 2 \cdot f(i-1) + f(i-3)$$

**Why not `f(i-2)` explicitly?**  
Unrolling `f(i-1) = 2·f(i-2) + f(i-4)` and substituting shows the two-horizontal-domino case is already captured inside `2·f(i-1)`. The clean closed recurrence is:

$$\boxed{f(i) = 2 \cdot f(i-1) + f(i-3)}$$

with base cases `f(1)=1, f(2)=2, f(3)=5`.

## Solution

**Approach**: Bottom-up DP with O(1) space using a rolling window of 3 values.

```python
class Solution:
    def numTilings(self, n: int) -> int:
        mod = 10**9 + 7

        if n == 1: return 1
        if n == 2: return 2
        if n == 3: return 5

        a, b, c = 1, 2, 5          # f(i-2), f(i-1), f(i)
        for i in range(n - 3):     # advance from i=4 up to i=n
            a, b, c = b, c, (2 * c + a) % mod
        return c
```

**Complexity**:
- Time: O(n)
- Space: O(1)

The commented-out top-down memoization is equivalent but uses O(n) stack and memo space; the iterative version is preferred.

# Tags

`dynamic-programming` `math`

