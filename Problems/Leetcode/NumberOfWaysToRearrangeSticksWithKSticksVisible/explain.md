## Problem

https://leetcode.com/problems/number-of-ways-to-rearrange-sticks-with-k-sticks-visible/description/

There are `n` uniquely-sized sticks whose lengths are integers from `1` to `n`. You want to arrange the sticks such that **exactly** `k` sticks are **visible** from the left. A stick is **visible** from the left if there are no longer sticks to the left of it.

Given `n` and `k`, return the number of such arrangements modulo `10^9 + 7`.

**Examples:**
- `n=3, k=2` → `3` (`[1,3,2]`, `[2,3,1]`, `[2,1,3]`)
- `n=5, k=5` → `1` (`[1,2,3,4,5]`)
- `n=20, k=11` → `647427950`

**Constraints:** `1 <= k <= n <= 1000`

---

## Observations

1. **Stick `n` is always visible.** It is the tallest stick, so it is always visible regardless of position. This means we never count it as a choice — it will always contribute exactly 1 visible stick when it is encountered from the left.

2. **Consider the role of the smallest stick (length 1).** When building an arrangement of `i` sticks with `k` visible, place the smallest stick somewhere:
   - If we place it **at the leftmost position**, it is visible (since nothing is to its left). The remaining `i-1` sticks must form an arrangement with `k-1` visible sticks → `F(i-1, k-1)` ways.
   - If we place it **anywhere other than the leftmost** (`i-1` choices), it is **never visible** because it is shorter than every other stick. The remaining `i-1` sticks still need `k` visible sticks among themselves → `(i-1) * F(i-1, k)` ways.

3. **Base cases:**
   - `F(0, 0) = 1`: empty arrangement with 0 visible sticks — exactly one way (do nothing).
   - `F(i, 0) = 0` for `i > 0`: impossible to have sticks with none visible.
   - `F(i, k) = 0` for `k > i`: cannot have more visible sticks than total sticks.

4. **Connection to Stirling numbers of the first kind.** `F(n, k)` equals the (unsigned) Stirling number of the first kind $\left[{n \atop k}\right]$, which counts permutations of `n` elements with exactly `k` cycles. The recurrence is identical: $\left[{n \atop k}\right] = \left[{n-1 \atop k-1}\right] + (n-1)\left[{n-1 \atop k}\right]$.

---

## Solution

```python
class Solution:
    def rearrangeSticks(self, n: int, k: int) -> int:
        mod = 10**9 + 7
        mem = {}

        def F(i: int, k: int) -> int:
            if i == 0 and k == 0:
                return 1
            if k == 0:
                return 0
            if k > i:
                return 0

            if (i, k) in mem:
                return mem[(i, k)]

            opt1 = F(i - 1, k - 1)          # place smallest at leftmost → visible
            opt2 = (i - 1) * F(i - 1, k)    # place smallest at any of (i-1) other positions → not visible
            res = (opt1 + opt2) % mod
            mem[(i, k)] = res
            return res

        return F(n, k)
```

**Recurrence:**

$$F(i, k) = F(i-1,\ k-1) + (i-1) \cdot F(i-1,\ k)$$

**Explanation of each term:**
- `F(i-1, k-1)` — put the smallest stick first; it is visible, so we need `k-1` more visible sticks from the remaining `i-1` sticks.
- `(i-1) * F(i-1, k)` — insert the smallest stick into any of the `i-1` non-first positions; it is never visible (always blocked), so we still need `k` visible sticks from the remaining `i-1` sticks.

**Complexity:**
- Time: $O(n \cdot k)$ — at most `n*k` unique subproblems, each solved in $O(1)$.
- Space: $O(n \cdot k)$ — memoization table.
