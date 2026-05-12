## Problem

https://leetcode.com/problems/coin-change/description

Given an integer array `coins` representing coins of different denominations and an integer `amount` representing a total amount of money, return the **fewest number of coins** needed to make up that amount. If that amount of money cannot be made up by any combination of the coins, return `-1`.

You may assume you have an **infinite number of each kind of coin**.

### Examples

**Example 1:**
- Input: `coins = [1,2,5]`, `amount = 11`
- Output: `3`
- Explanation: `11 = 5 + 5 + 1`

**Example 2:**
- Input: `coins = [2]`, `amount = 3`
- Output: `-1`

**Example 3:**
- Input: `coins = [1]`, `amount = 0`
- Output: `0`

### Constraints

- `1 <= coins.length <= 12`
- `1 <= coins[i] <= 2^31 - 1`
- `0 <= amount <= 10^4`

## Observations

1. **Optimal Substructure**: The minimum number of coins needed to make amount `i` depends on the minimum coins needed for amounts `i - coin` for each coin denomination. This is the hallmark of a dynamic programming problem.

2. **Recursive Nature**: We can think of this recursively: for each amount, we try using each coin and pick the option that gives us the minimum count.

3. **Overlapping Subproblems**: When solving recursively, we'll compute the minimum coins for the same amounts multiple times. For example, when computing amount 5, we might reach it via `5-1=4` and `5-2=3`, and both paths may later need the result for amount 3.

4. **Base Cases**:
   - Amount 0 requires 0 coins
   - Impossible amounts should be marked as infinity (or "impossible") to distinguish them from valid counts

5. **Greedy Won't Work**: Unlike the classic greedy algorithm (e.g., for making change with standard denominations), this problem requires considering all coins because some denominations might lead to suboptimal solutions.

## Solution

The solution presents two equivalent approaches:

### Approach 1: Top-Down Memoization (Commented Out)

```python
mem = {}
def F(i: int) -> int:
    if i < 0:
        return float('inf')
    if i == 0:
        return 0
    if i in mem:
        return mem[i]
    res = float('inf')
    for coin in coins:
        if coin <= i:
            opt = F(i - coin)
            if opt != float('inf'):
                res = min(res, 1 + opt)
    mem[i] = res
    return res
```

**How it works:**
- `F(i)` returns the minimum coins needed to make amount `i`
- **Base cases**: Return infinity for negative amounts (impossible), 0 for amount 0
- **Recursive case**: Try each coin, recursively solve for the remaining amount, take the minimum
- **Memoization**: Store results in `mem` dictionary to avoid recomputation

**Complexity:**
- Time: O(amount × n) where n is the number of coins
- Space: O(amount) for the memoization dictionary + O(amount) recursion depth

### Approach 2: Bottom-Up DP (Active Solution)

```python
dp = [float('inf')] * (amount + 1)
dp[0] = 0
for i in range(amount + 1):
    for coin in coins:
        if coin <= i and dp[i - coin] != float('inf'):
            dp[i] = min(dp[i], 1 + dp[i - coin])
return -1 if dp[amount] == float('inf') else dp[amount]
```

**How it works:**

1. **Initialize**: Create a DP array where `dp[i]` represents the minimum coins needed to make amount `i`. Set all to infinity except `dp[0] = 0`.

2. **Build up solutions**: For each amount from 1 to `amount`, try all coins:
   - If the coin doesn't exceed the current amount AND we can make `i - coin`
   - Update `dp[i]` with the minimum of current value and `1 + dp[i - coin]` (using one more coin)

3. **Return**: If `dp[amount]` is still infinity, it's impossible; otherwise return the result.

**Example Walkthrough** (coins = [1,2,5], amount = 11):

```
Initial: dp = [0, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf]

After processing amounts:
dp[0] = 0
dp[1] = 1 (using coin 1)
dp[2] = 1 (using coin 2)
dp[3] = 2 (using coins 1+2)
dp[4] = 2 (using coins 2+2)
dp[5] = 1 (using coin 5)
dp[6] = 2 (using coins 5+1)
dp[7] = 2 (using coins 5+2)
...
dp[11] = 3 (using coins 5+5+1)
```

**Complexity:**
- Time: O(amount × n) where n is the number of coins — we iterate through each amount and each coin
- Space: O(amount) for the DP array

### Why Bottom-Up Over Top-Down?

For this problem, bottom-up is preferred because:
- Avoids recursion stack overhead and potential stack overflow
- More cache-friendly (sequential array access)
- Cleaner code without recursion depth concerns

# Tags

#dynamic-programming #coin-change #unbounded-knapsack

