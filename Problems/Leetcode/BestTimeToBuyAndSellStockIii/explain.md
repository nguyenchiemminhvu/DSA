## Problem

https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description

You are given an array `prices` where `prices[i]` is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete **at most two transactions**.

**Note:** You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

### Examples

**Example 1:**
```
Input: prices = [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 3.
Total profit = 6.
```

**Example 2:**
```
Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 4.
Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions at the same time.
```

**Example 3:**
```
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
```

### Constraints

- `1 <= prices.length <= 10^5`
- `0 <= prices[i] <= 10^5`

## Observations

1. **At most 2 transactions**: We can buy and sell at most twice. A transaction consists of a buy followed by a sell.

2. **State representation**: At any day `i`, we need to track:
   - Whether we're currently holding a stock or not
   - How many complete transactions (buy + sell) we've done

3. **Key insight**: This is a dynamic programming problem where we need to explore all possibilities:
   - Skip the current day (do nothing)
   - Buy stock (if not holding and haven't done 2 transactions)
   - Sell stock (if holding)

4. **State transitions**:
   - If **not holding**: We can either buy the stock (transition to holding state) or skip it
   - If **holding**: We can either sell the stock (increment transaction count) or keep holding

5. **Time complexity**: O(n) where n is the length of prices array
   - Space complexity: O(n) for the DP table (can be optimized to O(1) with space optimization)

## Solution

### Approach: Dynamic Programming with State Tracking

We use a 3D DP table: `dp[i][hold][times]`
- `i`: current day (0 to n)
- `hold`: whether we're holding stock (0 = not holding, 1 = holding)
- `times`: number of completed transactions (0, 1, or 2)

**DP Definition:**
`dp[i][hold][times]` = maximum profit at day i with the given holding state and number of transactions completed

**Base Cases:**
- `dp[n][*][*] = 0` (no more days, profit = 0)
- `dp[*][*][2] = 0` (already done 2 transactions, can't do more)

**Transitions:**
- **Not holding** (`dp[i][0][times]`):
  - Skip this stock: `dp[i+1][0][times]`
  - Buy this stock: `-prices[i] + dp[i+1][1][times]` (we can hold it)
  - Maximum of above options

- **Holding** (`dp[i][1][times]`):
  - Keep holding: `dp[i+1][1][times]`
  - Sell this stock: `prices[i] + dp[i+1][0][times+1]` (completes a transaction, increment times)
  - Maximum of above options

**Answer:** `dp[0][0][0]` (start from day 0, not holding, 0 transactions done)

### Implementation

```python
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        
        # dp[i][hold][times] = max profit at day i with holding state and transaction count
        dp = [[[0] * 3 for _ in range(2)] for _ in range(n + 1)]
        
        # Fill DP table from the end backwards
        for i in range(n - 1, -1, -1):
            for times in range(2, -1, -1):
                if times >= 2:
                    # Already did 2 transactions, can't profit more
                    dp[i][0][times] = 0
                    dp[i][1][times] = 0
                else:
                    # Not holding stock
                    dp[i][0][times] = max(
                        dp[i + 1][0][times],      # skip this stock
                        -prices[i] + dp[i + 1][1][times]  # buy this stock
                    )
                    
                    # Holding stock
                    dp[i][1][times] = max(
                        dp[i + 1][1][times],      # keep holding
                        prices[i] + dp[i + 1][0][times + 1]  # sell this stock
                    )
        
        return dp[0][0][0]
```

### Complexity Analysis

- **Time Complexity:** O(n × 2 × 3) = O(n) where n is the length of prices
  - We iterate through each day, each holding state, and each transaction count
  
- **Space Complexity:** O(n × 2 × 3) = O(n)
  - DP table has dimensions n × 2 × 3
  - Can be optimized to O(1) by keeping only current and next day states

### Walkthrough with Example 1: prices = [3,3,5,0,0,3,1,4]

```
Day 0 (price=3): Can't profit yet
Day 1 (price=3): Still same price
Day 2 (price=5): Buy at 3, sell at 5, profit = 2
Day 3 (price=0): Low point, consider buying
Day 4 (price=0): Same low point
Day 5 (price=3): Sell at 3 if bought at 0, profit = 3
Day 6 (price=1): Can buy here for second transaction
Day 7 (price=4): Sell at 4, profit = 3
Total: 3 + 3 = 6
```

### Alternative: Memoized Recursion (Top-Down DP)

```python
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        mem = {}
        
        def F(i: int, hold: bool, times: int) -> int:
            if i >= n or times >= 2:
                return 0
            if (i, hold, times) in mem:
                return mem[(i, hold, times)]
            
            if not hold:
                # Not holding: buy or skip
                res = max(
                    -prices[i] + F(i + 1, True, times),  # buy
                    F(i + 1, False, times)  # skip
                )
            else:
                # Holding: sell or keep
                res = max(
                    prices[i] + F(i + 1, False, times + 1),  # sell
                    F(i + 1, True, times)  # keep holding
                )
            
            mem[(i, hold, times)] = res
            return res
        
        return F(0, False, 0)
```

# Tags

- Dynamic Programming
- State Machine
- Stock Trading
- Optimization Problems

