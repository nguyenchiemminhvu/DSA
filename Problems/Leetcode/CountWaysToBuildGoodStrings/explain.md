## Problem

https://leetcode.com/problems/count-ways-to-build-good-strings/description/

Given integers `zero`, `one`, `low`, and `high`, construct strings by starting with an empty string and repeatedly performing either:
- Append the character `'0'` exactly `zero` times, **or**
- Append the character `'1'` exactly `one` times.

A **good string** is any string built this way whose length is between `low` and `high` (inclusive).

Return the number of different good strings that can be constructed, modulo $10^9 + 7$.

**Example 1:**
```
Input:  low = 3, high = 3, zero = 1, one = 1
Output: 8
Explanation: All 8 binary strings of length 3 ("000" … "111") are good strings.
```

**Example 2:**
```
Input:  low = 2, high = 3, zero = 1, one = 2
Output: 5
Explanation: Good strings are "00", "11", "000", "110", "011".
```

**Constraints:**
- $1 \le \text{low} \le \text{high} \le 10^5$
- $1 \le \text{zero}, \text{one} \le \text{low}$

## Observations

1. **Two fixed-size "coins".**  
   At every step we can grow the current string by exactly `zero` characters or by exactly `one` characters. This is structurally identical to the **Coin Change II / unbounded knapsack** problem where the "coins" are `[zero, one]` and the "amount" is the target string length.

2. **Count, not existence.**  
   We need the total number of ways to reach each length $L$ in $[\text{low}, \text{high}]$. Concretely, `dp[L]` = number of distinct strings of length $L$ reachable from the empty string.

3. **Base case.**  
   `dp[0] = 1` — there is exactly one string of length 0: the empty string.

4. **Recurrence.**  
   To reach length `amount` we could have come from length `amount - zero` (by appending `zero` zeros) or from `amount - one` (by appending `one` ones):
   $$\text{dp}[\text{amount}] = \text{dp}[\text{amount} - \text{zero}] + \text{dp}[\text{amount} - \text{one}]$$
   (each term included only when the index is $\ge 0$).

5. **Answer accumulation.**  
   Sum `dp[amount]` for every `amount` in `[low, high]`.

6. **Two equivalent implementations** — top-down memoisation and bottom-up DP — both run in $O(\text{high})$ time and $O(\text{high})$ space.

## Solution

### Top-down (memoisation)

```python
class Solution:
    def countGoodStrings(self, low: int, high: int, zero: int, one: int) -> int:
        mod = 10**9 + 7
        coins = [zero, one]
        mem = {}

        def F(amount: int) -> int:
            if amount < 0:
                return 0
            if amount == 0:
                return 1
            if amount in mem:
                return mem[amount]
            ways = 0
            for c in coins:
                ways = (ways + F(amount - c)) % mod
            mem[amount] = ways
            return ways

        res = 0
        for i in range(low, high + 1):
            res = (res + F(i)) % mod
        return res
```

`F(amount)` asks: *in how many ways can I build a string of exactly this length?*  
It tries subtracting each coin from `amount` and sums the recursive results, memoising to avoid recomputation.

### Bottom-up (tabulation)  ← submitted solution

```python
class Solution:
    def countGoodStrings(self, low: int, high: int, zero: int, one: int) -> int:
        mod = 10**9 + 7
        coins = [zero, one]

        dp = [0] * (high + 1)
        dp[0] = 1          # empty string — one way to have length 0
        res = 0

        for amount in range(high + 1):
            for c in coins:
                if c <= amount:
                    dp[amount] = (dp[amount] + dp[amount - c]) % mod
            if low <= amount <= high:
                res = (res + dp[amount]) % mod

        return res
```

**Walk-through (Example 2 — low=2, high=3, zero=1, one=2):**

| `amount` | from `dp[amount-1]` (+zero) | from `dp[amount-2]` (+one) | `dp[amount]` | in range? |
|----------|-----------------------------|----------------------------|--------------|-----------|
| 0        | —                           | —                          | 1            | no        |
| 1        | dp[0] = 1                   | —                          | 1            | no        |
| 2        | dp[1] = 1                   | dp[0] = 1                  | 2            | yes → res=2 |
| 3        | dp[2] = 2                   | dp[1] = 1                  | 3            | yes → res=5 |

Final answer: **5** ✓

**Complexity:**
- Time: $O(\text{high} \times 2) = O(\text{high})$
- Space: $O(\text{high})$ for the `dp` array

# Tags

`Dynamic Programming` `Unbounded Knapsack` `Bottom-up DP` `Memoisation`

