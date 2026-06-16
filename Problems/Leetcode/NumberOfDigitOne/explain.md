## Problem

https://leetcode.com/problems/number-of-digit-one/

Given an integer `n`, count the total number of digit `1` appearing in all
non-negative integers less than or equal to `n`.

**Example 1:**

```
Input:  n = 13
Output: 6
```

Explanation: the digit `1` appears in `1, 10, 11, 12, 13`. Note that `11`
contributes two `1`s, so the total is `1 + 1 + 1 + 2 + 1 = 6`.

**Example 2:**

```
Input:  n = 0
Output: 0
```

**Constraints:**

- `0 <= n <= 10^9`

## Observations

1. We are not counting numbers that *contain* a `1`; we are counting
   *occurrences* of the digit `1` across every position of every integer in
   `[0, n]`. The number `11` contributes `2`, not `1`.
2. Brute force (loop `i` from `0` to `n`, count `1`s in `str(i)`) costs
   `O(n * log10(n))`. With `n` up to `10^9` this is ~`10^10` operations, far
   too slow. We need to count *per digit position* instead of per number.
3. Any integer in `[0, n]` can be written as a length-`L` decimal string
   (zero-padded on the left), where `L = len(str(n))`. We build such a string
   digit by digit from the most significant position.
4. While building, the only thing that matters for the future is:
   - the current position `i`,
   - how many `1`s we have placed so far (`count`),
   - whether we are still bounded by `n`'s prefix (`is_tight`).
   If `is_tight` is `False`, the remaining positions can be any digit `0..9`
   freely; that subproblem depends only on `(i, count, False)` and is reusable.
   This is the standard *digit DP* setup.
5. `is_tight` means: every digit chosen so far equals the corresponding digit
   of `n`. Under that constraint the next digit can range only from `0` to
   `s[i]`; otherwise it can range from `0` to `9`. Tightness is "sticky
   downward": once we pick a digit strictly less than `s[i]`, we are free for
   the rest of the number.
6. We don't need to special-case leading zeros for *this* problem: a leading
   zero is just a `0`, which contributes nothing to the count of `1`s, so the
   zero-padded view gives the same answer as the unpadded view.

## Solution

Digit DP that enumerates every number in `[0, n]` exactly once by fixing
digits left-to-right.

State: `F(i, count, is_tight)`

- `i`        — index of the next digit to place (`0` = most significant).
- `count`    — number of `1`s placed in positions `0..i-1`.
- `is_tight` — whether the prefix so far equals `n`'s prefix.

Transition. Let `limit = s[i]` if `is_tight` else `9`. For each
`digit` in `0..limit`:

- `next_tight = is_tight and digit == limit`
- `next_count = count + (1 if digit == 1 else 0)`
- recurse into `F(i+1, next_count, next_tight)`.

Base case. When `i == L`, we have built one full number in `[0, n]`; its
contribution to the answer is the number of `1`s it contains, which is
exactly `count`. So `return count`.

Answer. `F(0, 0, True)` — start at the most significant digit, no `1`s yet,
bounded by `n`.

```python
class Solution:
    def countDigitOne(self, n: int) -> int:
        s = str(n)
        L = len(s)

        from functools import lru_cache
        @lru_cache(None)
        def F(i: int, count: int, is_tight: bool) -> int:
            if i >= L:
                return count
            limit = int(s[i]) if is_tight else 9
            total = 0
            for digit in range(limit + 1):
                next_tight = is_tight and digit == limit
                next_count = count + (1 if digit == 1 else 0)
                total += F(i + 1, next_count, next_tight)
            return total

        return F(0, 0, True)
```

### Why this is correct

- The recursion enumerates each integer in `[0, n]` exactly once: at every
  level we branch over all legal next digits, and the `is_tight` flag enforces
  the upper bound `n` (digits beyond `s[i]` are forbidden while tight).
- At the leaf, returning `count` adds that integer's `1`-count to the total.
  Summing leaves gives the total occurrences of `1` across `[0, n]`, which is
  exactly the quantity asked for.

### Complexity

Let `L = len(str(n))` (so `L <= 10` for the given constraint).

- States: `i` has `L` values, `count` has at most `L+1` values, `is_tight`
  has `2` values → `O(L^2)` states.
- Each state does `O(10)` work in the digit loop.
- Total time: `O(L^2 * 10)` — a few hundred operations for `n <= 10^9`.
- Memory: `O(L^2)` for the memo plus `O(L)` recursion stack.

### A subtle point about memoization

`count` is carried into the state, so two prefixes that have placed a
different number of `1`s are *different* memo entries even though their
future choices are identical. That is wasteful but still `O(L^2)` and well
within limits. A common alternative is to *not* carry `count` in the state
and instead let `F(i, is_tight)` return the number of `1`s contributed by
the *suffix* starting at `i`; the caller then adds `1`s contributed by the
chosen digit itself. Both formulations give the same answer; the version
above is the most direct translation of "build the number, then count its
`1`s at the leaf."
