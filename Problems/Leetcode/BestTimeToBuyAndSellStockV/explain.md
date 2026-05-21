## Problem

https://leetcode.com/problems/best-time-to-buy-and-sell-stock-v/description/?q=stock

```
Given an integer array `prices` where `prices[i]` is the price of a stock in dollars on the ith day, and an integer `k`.

You are allowed to make at most `k` transactions, where each transaction can be either of the following:

1. **Normal transaction**: Buy on day i, then sell on a later day j where i < j. You profit `prices[j] - prices[i]`.

2. **Short selling transaction**: Sell on day i, then buy back on a later day j where i < j. You profit `prices[i] - prices[j]`.

Note that you must complete each transaction before starting another. Additionally, you can't buy or sell on the same day you are selling or buying back as part of a previous transaction.

Return the maximum total profit you can earn by making at most k transactions.

**Constraints:**
- 2 <= prices.length <= 10³
- 1 <= prices[i] <= 10⁹
- 1 <= k <= prices.length / 2

**Examples:**

Example 1:
- Input: prices = [1,7,9,8,2], k = 2
- Output: 14
- Explanation: Buy at 1, sell at 9 (profit 8). Short sell at 8, buy back at 2 (profit 6). Total: 14.

Example 2:
- Input: prices = [12,16,19,19,8,1,19,13,9], k = 3
- Output: 36
- Explanation: Buy at 12, sell at 19 (profit 7). Short sell at 19, buy back at 8 (profit 11). Buy at 1, sell at 19 (profit 18). Total: 36.
```

## Observations

1. **State-based Dynamic Programming**: We need to track three pieces of information:
   - Current day `i`
   - Number of transactions completed `t`
   - Current state: 0 (no position), 1 (holding stock), 2 (in short position)

2. **State Transitions**:
   - State 0 (no position): Can transition to state 1 (buy) or state 2 (short sell), or skip the day
   - State 1 (holding stock): Can only sell (transition to state 0), completing a transaction
   - State 2 (short position): Can only buy back (transition to state 0), completing a transaction

3. **Transaction Counting**: A transaction is complete when we return to state 0. Each buy-sell or sell-buy cycle counts as one transaction.

4. **Key Insight**: Unlike buying and selling alone, we need to track if we're in a "holding" state or a "short" state because the next action depends on which position we're in.

5. **Time Complexity**: O(n × k × 3) = O(n × k) where n is the length of prices.

6. **Space Complexity**: O(n × k × 3) = O(n × k) for the DP table.

## Solution

### Approach: 3D Dynamic Programming

The solution uses 3D DP where:
- `dp[i][t][state]` = maximum profit from day i to end, having completed t transactions, currently in the given state
- States: 0 = ready to trade, 1 = holding stock, 2 = short position

**Transitions:**

From state 0:
- Skip: `dp[i+1][t][0]` (don't trade today)
- Buy (enter state 1): `-prices[i] + dp[i+1][t][1]` (spend money to buy)
- Short sell (enter state 2): `prices[i] + dp[i+1][t][2]` (receive money from short selling)

From state 1 (holding stock):
- Sell (complete transaction): `prices[i] + dp[i+1][t+1][0]` (if t < k)
- Skip: `dp[i+1][t][1]`

From state 2 (short position):
- Buy back (complete transaction): `-prices[i] + dp[i+1][t+1][0]` (if t < k)
- Skip: `dp[i+1][t][2]`

**Base Case:**
- When i >= n (end of days): return 0 if state == 0 (no open position), else return -∞ (invalid)

**Algorithm:**

```python
def maximumProfit(self, prices: List[int], k: int) -> int:
    n = len(prices)
    INF = float('-inf')
    
    # dp[i][t][state] = max profit from day i with t transactions completed in given state
    # state: 0 = ready, 1 = holding, 2 = short
    dp = [[[INF] * 3 for _ in range(k + 1)] for _ in range(n + 1)]
    
    # Base case: after all days, only state 0 is valid
    for t in range(k + 1):
        dp[n][t][0] = 0
    
    # Fill DP table backwards from day n-1 to 0
    for i in range(n - 1, -1, -1):
        for t in range(k, -1, -1):
            for state in range(3):
                # Option 1: Skip this day
                dp[i][t][state] = dp[i + 1][t][state]
                
                if state == 0:
                    # Can buy or short sell
                    dp[i][t][state] = max(
                        dp[i][t][state],
                        -prices[i] + dp[i + 1][t][1],      # Buy
                        prices[i] + dp[i + 1][t][2]         # Short sell
                    )
                elif state == 1:
                    # Holding stock, can only sell if transactions remaining
                    if t < k:
                        dp[i][t][state] = max(
                            dp[i][t][state],
                            prices[i] + dp[i + 1][t + 1][0]  # Sell
                        )
                elif state == 2:
                    # Short position, can only buy back if transactions remaining
                    if t < k:
                        dp[i][t][state] = max(
                            dp[i][t][state],
                            -prices[i] + dp[i + 1][t + 1][0]  # Buy back
                        )
    
    return dp[0][0][0]
```

**Walkthrough with Example 1** (prices = [1,7,9,8,2], k = 2):

1. Day 4 (price=2): Only state 0 with value 0
2. Day 3 (price=8): 
   - In state 0: can short sell for +8, leading to state 2
3. Day 2 (price=9):
   - In state 0: can buy for -9, leading to state 1
   - After buying at 1 and selling at 9: +8
4. Day 1 (price=7): Skip or transition
5. Day 0 (price=1):
   - Buy at 1 → sell at 9 (profit 8)
   - Short at 8 → buy back at 2 (profit 6)
   - Total: 14 ✓

### Why This Works

The key is separating the states and only allowing transitions that make sense:
- Can't sell without buying first (state 1 required before moving to state 0 from buy)
- Can't buy back without shorting first (state 2 required before moving to state 0 from short)
- Transactions are counted only when returning to state 0 (complete buy-sell or sell-buy)
- The backward DP ensures we see all future opportunities before making decisions
```

## Solution Explanation

**Why Dynamic Programming?**

This problem has overlapping subproblems and optimal substructure:
- Many days may have the same states and transaction counts
- The optimal solution for a given state can be built from optimal solutions of future states
- We can memoize or use tabulation to avoid recalculating

**Why Three States?**

Without distinguishing between holding stock and being in a short position, we can't properly enforce the constraints:
- If holding stock, the only valid next transaction is to sell
- If in short position, the only valid next transaction is to buy back
- If in no position (state 0), we can start either type of transaction

**Correctness Guarantees:**

1. Never violates transaction sequence (buy before sell, sell before buy back)
2. Respects the k transaction limit through the t parameter
3. Respects the "can't buy/sell on same day" constraint by advancing to next day
4. Finds optimal profit through exhaustive state exploration

# Tags

- Dynamic Programming
- Stock Trading
- State Machine
- Multiple Transactions
- Short Selling

