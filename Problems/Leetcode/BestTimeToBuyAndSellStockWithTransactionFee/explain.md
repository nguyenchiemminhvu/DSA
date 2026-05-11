## Problem

https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/description

You are given an array `prices` where `prices[i]` is the price of a given stock on the ith day, and an integer `fee` representing a transaction fee.

Find the maximum profit you can achieve. You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.

**Note:**
- You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
- The transaction fee is only charged once for each stock purchase and sale.

**Example 1:**
```
Input: prices = [1,3,2,8,4,9], fee = 2
Output: 8
Explanation: The maximum profit can be achieved by:
- Buying at prices[0] = 1
- Selling at prices[3] = 8
- Buying at prices[4] = 4
- Selling at prices[5] = 9
The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.
```

**Example 2:**
```
Input: prices = [1,3,7,5,10,3], fee = 3
Output: 6
```

**Constraints:**
- `1 <= prices.length <= 5 * 10^4`
- `1 <= prices[i] < 5 * 10^4`
- `0 <= fee < 5 * 10^4`

## Observations

1. **State-based approach**: At any day, we can be in one of two states:
   - **Not holding** a stock: We can either do nothing or buy a stock (paying the fee)
   - **Holding** a stock: We can either do nothing or sell the stock

2. **Optimal substructure**: The profit at day `i` depends on the maximum profit we can achieve up to day `i-1` in both states.

3. **Greedy insight**: We should sell whenever the price increases (and buying was profitable), since multiple small transactions are equivalent to one large transaction and we only pay the fee once per buy-sell pair.

4. **Transaction fee timing**: The fee is deducted when we **buy** the stock, making the effective purchase price = `prices[i] + fee`.

5. **No constraints on number of transactions**: Unlike other variants, we can do unlimited transactions, so we greedily capture all profitable opportunities.

## Solution

### Approach: Dynamic Programming (Bottom-Up Tabulation)

**State Definition:**
- `dp[0][i]` = Maximum profit at day `i` when **not holding** stock
- `dp[1][i]` = Maximum profit at day `i` when **holding** stock

**Transitions (iterating from day n-1 to 0):**

For each day `i`:
- **Not holding** (dp[0][i]): Either we didn't do anything today, or we sold the stock we were holding
  ```
  dp[0][i] = max(dp[0][i+1],              // do nothing
                 dp[1][i+1] - prices[i])  // sell at prices[i]
  ```
  Note: We already paid the fee when we bought, so no fee here

- **Holding** (dp[1][i]): Either we didn't do anything today, or we bought the stock today
  ```
  dp[1][i] = max(dp[1][i+1],                           // do nothing (hold)
                 dp[0][i+1] - prices[i] - fee)         // buy at prices[i], pay fee
  ```

**Base Case:**
- `dp[0][n] = 0` (no stock, no profit)
- `dp[1][n] = 0` (can't hold past the last day)

**Answer:** `dp[0][0]` - maximum profit starting from day 0 in "not holding" state

**Time Complexity:** $O(n)$ - single pass through the prices array

**Space Complexity:** $O(n)$ - we use a 2×(n+1) DP table. Can be optimized to $O(1)$ by tracking only the previous states.

### Code Explanation

```python
class Solution:
    def maxProfit(self, prices: List[int], fee: int) -> int:
        n = len(prices)
        
        # dp[state][day] where state: 0 = not holding, 1 = holding
        dp = [[0 for _ in range(n + 1)] for _ in range(2)]
        
        # Process days in reverse (from day n-1 to 0)
        for i in range(n - 1, -1, -1):
            # Not holding: either do nothing or sell today
            dp[0][i] = max(dp[0][i + 1], dp[1][i + 1] - prices[i])
            
            # Holding: either do nothing or buy today (with fee)
            dp[1][i] = max(dp[1][i + 1], dp[0][i + 1] - prices[i] - fee)
        
        return dp[0][0]  # Start from day 0, not holding any stock
```

### Alternative: Memoized Recursion (Top-Down)

The commented code shows the memoized approach:
- `F(i, hold)` returns max profit from day `i` onwards
- Base case: `F(n, hold) = 0`
- At each step, we either do nothing (move to next day with same state) or perform an action

Both approaches have the same complexity; the iterative DP version avoids recursion overhead.

# Tags
Dynamic Programming | State Machine | Greedy | Stock Trading

