## Problem

https://leetcode.com/problems/guess-number-higher-or-lower-ii/description

We play a guessing game over integers `[1, n]`. We pick a pivot `x` to guess:
- If correct, we pay nothing more.
- If the answer is higher, the search space shrinks to `[x+1, r]`.
- If the answer is lower, the search space shrinks to `[l, x-1]`.

Each wrong guess of `x` costs `$x`. We want the **minimum guaranteed cost** to find the number, regardless of what the adversary picks.

**Examples:**
- `n = 1` → `0` (only one number, no wrong guess possible)
- `n = 2` → `1` (guess 1; if wrong, pay $1 and guess 2)
- `n = 10` → `16` (optimal strategy shown below)

**Constraints:** `1 <= n <= 200`

---

## Observations

1. **Minimax structure.** The player wants to minimize cost; the adversary always picks the worst branch (maximizes cost). For a given guess `x` in range `[l, r]`, the cost is:
   $$x + \max(F(l, x-1),\ F(x+1, r))$$
   where `F(l, r)` is the minimum guaranteed cost over `[l, r]`.

2. **Base cases.**
   - `l >= r`: only zero or one number remains, no payment needed → `F(l, r) = 0`.
   - `l + 1 == r`: two numbers remain. Always guess the smaller one (`l`); worst case pay `$l` → `F(l, r) = l`.

3. **Optimal pivot is NOT always the midpoint.** Unlike binary search (minimizing comparisons), here the cost of a wrong guess equals the guessed value. Guessing low is cheap but leaves a large right sub-range; guessing high is expensive but leaves a small right sub-range. The optimal pivot balances these asymmetric costs.

4. **Overlapping subproblems.** Any strategy over `[1, n]` recurses into overlapping sub-ranges, making memoization (or bottom-up DP) effective.

5. **Complexity.** There are $O(n^2)$ unique ranges and $O(n)$ pivot choices per range, giving $O(n^3)$ time and $O(n^2)$ space.

---

## Solution

### Approach: Top-down DP (Memoization)

Define `F(l, r)` = minimum amount of money guaranteed to find the number in `[l, r]`.

**Recurrence:**
$$F(l, r) = \min_{x=l}^{r} \bigl[ x + \max(F(l, x-1),\ F(x+1, r)) \bigr]$$

**Base case:** `F(l, r) = 0` when `l >= r`.

```python
class Solution:
    def getMoneyAmount(self, n: int) -> int:
        mem = {}
        def F(l: int, r: int) -> int:
            if l >= r:
                return 0
            if (l, r) in mem:
                return mem[(l, r)]
            res = float('inf')
            for x in range(l, r + 1):
                res = min(res, x + max(F(l, x - 1), F(x + 1, r)))
            mem[(l, r)] = res
            return res
        return F(1, n)
```

**Walkthrough for `n = 10`:**

| Call | Best pivot | Cost |
|------|-----------|------|
| `F(1,10)` | 7 | `7 + max(F(1,6), F(8,10))` = `7 + max(8, 9)` = **16** |
| `F(8,10)` | 9 | `9 + max(F(8,8), F(10,10))` = `9 + 0` = **9** |
| `F(1,6)` | 3 | `3 + max(F(1,2), F(4,6))` = `3 + max(1, 5)` = **8** |
| `F(4,6)` | 5 | `5 + max(F(4,4), F(6,6))` = `5 + 0` = **5** |
| `F(1,2)` | 1 | `1 + max(0, F(2,2))` = `1 + 0` = **1** |

Result: `F(1,10) = 16`. ✓

---

### Additional Optimization: Pivot search range reduction

When searching for the best pivot in `[l, r]`, we can restrict the search to the range **`[l, (l+r)/2]`** (i.e., the lower half). Here is why:

- For any pivot `x > mid`, the left sub-range `[l, x-1]` is strictly larger than the right sub-range `[x+1, r]`, meaning `F(l, x-1) >= F(x+1, r)` in all but degenerate cases.
- Since we pay `x` (which is already large) and also inherit the cost of the larger left sub-range, pivoting above the midpoint is almost always dominated.
- Specifically: if `x > mid` then `F(l, x-1) > F(x+1, r)` whenever the subproblems are symmetric, so `x + F(l, x-1)` only grows as `x` moves right.

In practice this halves the inner loop, reducing the constant factor without changing the asymptotic $O(n^3)$ complexity.

```python
class Solution:
    def getMoneyAmount(self, n: int) -> int:
        mem = {}
        def F(l: int, r: int) -> int:
            if l >= r:
                return 0
            if (l, r) in mem:
                return mem[(l, r)]
            mid = (l + r) // 2
            res = float('inf')
            for x in range(mid, r + 1):          # search [mid, r] only
                cost = x + max(F(l, x - 1), F(x + 1, r))
                res = min(res, cost)
                if F(l, x - 1) >= F(x + 1, r):  # left side dominates; going higher won't help
                    break
            mem[(l, r)] = res
            return res
        return F(1, n)
```

> **Why start at `mid` and break early?**
> Once the left sub-cost exceeds the right sub-cost, increasing `x` further raises both `x` itself and keeps `F(l, x-1)` non-decreasing, so the total can only worsen. We break as soon as `F(l, x-1) >= F(x+1, r)`.

---

# Tags

`Dynamic Programming` `Minimax` `Memoization` `Interval DP`

