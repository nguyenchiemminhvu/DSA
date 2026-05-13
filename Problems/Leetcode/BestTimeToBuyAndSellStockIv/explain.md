## Problem

https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/description

Given an integer array `prices` where `prices[i]` is the price of a given stock on the ith day, and an integer `k`.

**Find the maximum profit you can achieve.** You may complete at most `k` transactions: i.e. you may buy at most `k` times and sell at most `k` times.

**Note:** You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

### Examples

**Example 1:**
```
Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
```

**Example 2:**
```
Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. 
Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
```

### Constraints

- $1 \leq k \leq 100$
- $1 \leq \text{prices.length} \leq 1000$
- $0 \leq \text{prices}[i] \leq 1000$

## Observations

1. **State Space**: At each day, we need to track:
   - Current day index `i`
   - Whether we currently hold a stock (`hold = 0` or `1`)
   - Number of completed transactions so far (`times = 0` to `k`)

2. **Transaction Definition**: A transaction consists of one buy followed by one sell. We count completed transactions when we sell.

3. **Decision Tree**: At each state, we have choices:
   - If **not holding**: Buy (move to holding state, same transaction count) or Skip
   - If **holding**: Sell (move to not holding state, increment transaction count) or Keep holding

4. **Base Cases**:
   - At the end of prices (`i >= n`), profit is 0
   - When we've already completed `k` transactions (`times >= k`), we can't make more profit

5. **Recurrence Relation**:
   - `dp[i][0][times]` = max profit at day `i`, not holding stock, completed `times` transactions
   - `dp[i][1][times]` = max profit at day `i`, holding stock, completed `times` transactions
   
   Transitions:
   - `dp[i][0][times] = max(dp[i+1][0][times], -prices[i] + dp[i+1][1][times])`
     - Either skip this day or buy at this price
   - `dp[i][1][times] = max(dp[i+1][1][times], prices[i] + dp[i+1][0][times+1])`
     - Either keep holding or sell and complete a transaction

## Solution

### Approach: Dynamic Programming (Tabulation)

This solution uses bottom-up DP to avoid the overhead of recursion while solving the stock trading problem with transaction limits.

**State Definition:**
- `dp[i][hold][times]` represents the maximum profit when:
  - We are at day `i`
  - `hold = 0` means we don't have stock in hand, `hold = 1` means we have stock
  - `times` represents the number of completed transactions (buy-sell pairs) so far

**Space:** $O(n \times 2 \times (k+1)) = O(n \cdot k)$

**Time:** $O(n \times k)$ since we iterate through `n` days and `k` transaction counts

**Key Insights:**

1. **No holding constraint**: We count the transaction when we **sell**, not when we buy. This ensures we can track completed transactions accurately.

2. **Why not holding first?**: We initialize from the state where we don't hold a stock (`dp[i][0][times]`), which allows us to either buy or skip.

3. **Backward iteration**: We iterate from the last day backwards to the first day because:
   - Future states (`dp[i+1][...]`) are already computed
   - We can make decisions based on what's optimal ahead

4. **Transition logic**:
   - When **not holding**: We can either skip today or buy at today's price (losing that amount from profit)
   - When **holding**: We can either keep holding or sell today (gaining that amount to profit) and increment transaction count

5. **Final answer**: `dp[0][0][0]` represents starting from day 0, without holding stock, with 0 completed transactions—the optimal strategy.

**Example Trace (k=2, prices=[3,2,6,5,0,3]):**

Starting from day 5 (price=3) and working backwards:

```
Day 5 (price=3):
- dp[5][0][0] = 0 (can skip or need capital)
- dp[5][1][0] = -3 (buy at 3)

Day 4 (price=0):
- dp[4][0][0] = 0 (skip day 4)
- dp[4][1][0] = max(-0 + dp[5][1][0], dp[5][1][0]) = max(-3, -3) = -3
- dp[4][0][1] = max(0 + dp[5][0][2], dp[5][0][1]) = 0
- dp[4][1][1] = -0 + dp[5][0][1] = 0

Day 3 (price=5):
- Can buy at 5 and later sell at higher prices
- Tracks various combinations of holding/not holding and transaction counts

... and so on until we reach dp[0][0][0]
```

The maximum profit is achieved by: **Buy at 2, Sell at 6 (profit=4), Buy at 0, Sell at 3 (profit=3), Total=7**.

### Code Explanation

```python
def maxProfit(self, k: int, prices: List[int]) -> int:
    n = len(prices)
    
    # Create 3D DP table: dp[day][holding_status][transactions_completed]
    dp = [[[0] * (k + 1) for _ in range(2)] for _ in range(n + 1)]
    
    # Base cases: dp[n][...][...] = 0 and dp[i][...][k] = 0 are already set
    
    # Fill DP table backwards from day n-1 to day 0
    for i in range(n - 1, -1, -1):
        for times in range(k - 1, -1, -1):
            # Not holding stock at day i with 'times' completed transactions
            dp[i][0][times] = max(
                dp[i + 1][0][times],           # Skip this day
                -prices[i] + dp[i + 1][1][times]  # Buy at prices[i]
            )
            
            # Holding stock at day i with 'times' completed transactions
            dp[i][1][times] = max(
                dp[i + 1][1][times],           # Keep holding
                prices[i] + dp[i + 1][0][times + 1]  # Sell and complete transaction
            )
    
    return dp[0][0][0]
```

**Why the order matters:**
- We iterate `times` from `k-1` down to `0` to ensure when we calculate selling (which increments `times`), the corresponding state is already computed
- We iterate `i` from `n-1` down to `0` because transitions depend on `dp[i+1][...]`

### Alternative Approach: Memoization (Top-Down DP)

The commented-out code shows the memoized recursive approach:

```python
mem = {}
def F(i: int, hold: bool, times: int) -> int:
    if i >= n or times >= k:
        return 0
    if (i, hold, times) in mem:
        return mem[(i, hold, times)]
    
    if not hold:
        res = max(
            F(i + 1, False, times),          # Skip
            -prices[i] + F(i + 1, True, times)  # Buy
        )
    else:
        res = max(
            F(i + 1, True, times),           # Keep holding
            prices[i] + F(i + 1, False, times + 1)  # Sell
        )
    
    mem[(i, hold, times)] = res
    return res

return F(0, False, 0)
```

Both approaches have the same time and space complexity, but the tabulation approach avoids recursion overhead.

# Tags

- Dynamic Programming
- Stock Trading
- State Machine
- Transaction Limit
- Tabulation vs Memoization

