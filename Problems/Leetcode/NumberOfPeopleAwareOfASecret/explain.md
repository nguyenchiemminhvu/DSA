## Problem

https://leetcode.com/problems/number-of-people-aware-of-a-secret/description

On day 1, one person discovers a secret. Each person will share the secret with a new person every day, starting from `delay` days after discovering it. Each person will forget the secret `forget` days after discovering it (and cannot share on or after the forget day).

Given integers `n`, `delay`, and `forget`, return the number of people who know the secret at the end of day `n`, modulo $10^9 + 7$.

**Constraints:**
- $2 \leq n \leq 1000$
- $1 \leq \text{delay} < \text{forget} \leq n$

**Examples:**
- `n=6, delay=2, forget=4` → `5`
- `n=4, delay=1, forget=3` → `6`

## Observations

1. **A person discovered the secret on day `i` can share it on days `[i+delay, i+forget-1]`** (inclusive). They start sharing `delay` days after discovery and forget after `forget` days, so they can no longer share on day `i+forget` onwards.

2. **`dp[i]` = number of new people who first learn the secret on day `i`.**  
   A person who learned the secret on day `j` will share with someone new on day `i` if and only if:
   - They haven't forgotten yet: $j + \text{forget} > i \Rightarrow j > i - \text{forget}$, i.e. $j \geq i - \text{forget} + 1$
   - They have already passed the delay: $j + \text{delay} \leq i \Rightarrow j \leq i - \text{delay}$

   So the people who can spread the secret to someone new on day `i` are exactly those who discovered it on days in the window $[i - \text{forget} + 1,\ i - \text{delay}]$.

3. **The recurrence is:**
$$dp[i] = \sum_{j=\max(1,\, i-\text{forget}+1)}^{i-\text{delay}} dp[j]$$
   with base case $dp[1] = 1$.

4. **Final answer:** At the end of day `n`, the people who still *know* the secret are those who discovered it on days $[n - \text{forget} + 1,\ n]$ (they haven't forgotten yet). So the answer is:
$$\sum_{i=n-\text{forget}+1}^{n} dp[i] \pmod{10^9+7}$$

5. **Optimization note:** The inner sum over a sliding window can be maintained with a running prefix sum to reduce the per-day cost from $O(\text{forget})$ to $O(1)$, giving an overall $O(n)$ solution. The straightforward nested loop is $O(n \cdot \text{forget})$, which is fine for $n \leq 1000$.

## Solution

```python
class Solution:
    def peopleAwareOfSecret(self, n: int, delay: int, forget: int) -> int:
        mod = 10**9 + 7

        # dp[i] = number of people who first learn the secret on day i
        dp = [0] * (n + 1)
        dp[1] = 1

        for i in range(2, n + 1):
            # People who discovered the secret in [left, right] can share on day i
            left = i - forget + 1
            right = i - delay
            for j in range(left, right + 1):
                if j >= 1:
                    dp[i] = (dp[i] + dp[j]) % mod

        # People still knowing the secret on day n: discovered in [n-forget+1, n]
        return sum(dp[n - forget + 1 : n + 1]) % mod
```

**Complexity:**
- Time: $O(n \cdot \text{forget})$
- Space: $O(n)$

# Tags
`Dynamic Programming` `Sliding Window`
