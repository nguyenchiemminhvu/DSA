## Problem

https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/description

You are given an array `prices` where `prices[i]` is the price of a given stock on the ith day.

Find the **maximum profit** you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:

- After you sell your stock, you **cannot buy stock on the next day** (i.e., cooldown one day).
- You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

**Example 1:**
```
Input: prices = [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]
```

**Example 2:**
```
Input: prices = [1]
Output: 0
```

**Constraints:**
- `1 <= prices.length <= 5000`
- `0 <= prices[i] <= 1000`

## Observations

1. **State-based problem**: At any day `i`, we're either holding a stock or not holding. This is a natural fit for DP with states.

2. **Cooldown constraint**: After selling on day `i`, we can only buy again on day `i+2` (since day `i+1` is cooldown). This is key to the state transitions.

3. **No initial stock**: We start with 0 profit and are not holding any stock.

4. **State definition**:
   - `dp[i][0]` = max profit at day `i` when we're **not holding** stock
   - `dp[i][1]` = max profit at day `i` when we're **holding** stock

5. **State transitions**:
   - To **not hold** on day `i`:
     - Either we buy on day `i`: `-prices[i] + dp[i+1][1]` (move to holding state)
     - Or we skip/do nothing on day `i`: `dp[i+1][0]` (stay in not-holding state)
   - To **hold** on day `i`:
     - Either we sell on day `i`: `prices[i] + dp[i+2][0]` (jump to `i+2` due to cooldown)
     - Or we skip on day `i`: `dp[i+1][1]` (stay in holding state)

6. **Base case**: At day `n` and beyond, profit is 0 (no more days to trade).

7. **Answer**: `dp[0][0]` (we start from day 0 in not-holding state, maximizing profit).

## Solution

### Approach 1: Top-Down Memoization (Recursion)

```python
def maxProfit(prices):
    n = len(prices)
    mem = {}
    
    def F(i: int, hold: bool) -> int:
        # i: current day
        # hold: whether we're currently holding stock
        if i >= n:
            return 0
        if (i, hold) in mem:
            return mem[(i, hold)]
        
        res = 0
        if not hold:
            # Not holding: decide to buy or skip
            res = max(
                -prices[i] + F(i + 1, True),  # buy stock today
                F(i + 1, False)                 # skip today
            )
        else:
            # Holding: decide to sell or skip
            res = max(
                prices[i] + F(i + 2, False),    # sell stock today (skip i+1 due to cooldown)
                F(i + 1, True)                  # skip today, still holding
            )
        
        mem[(i, hold)] = res
        return res
    
    return F(0, False)
```

**Intuition**: 
- We recursively explore all possible decisions at each day
- Memoization avoids recomputing the same subproblems
- Time: O(n), Space: O(n) for memoization table

### Approach 2: Bottom-Up DP (Iterative)

```python
def maxProfit(prices):
    n = len(prices)
    
    # dp[i][0] = max profit on day i when not holding
    # dp[i][1] = max profit on day i when holding
    dp = [[0] * 2 for _ in range(n + 2)]
    # dp[n] and dp[n+1] are already 0 (base case)
    
    # Process days in reverse order (from n-1 to 0)
    for i in range(n - 1, -1, -1):
        # Not holding on day i
        dp[i][0] = max(
            -prices[i] + dp[i + 1][1],  # buy stock today
            dp[i + 1][0]                 # skip today
        )
        
        # Holding on day i
        dp[i][1] = max(
            prices[i] + dp[i + 2][0],    # sell stock today (cooldown affects i+1)
            dp[i + 1][1]                 # skip today, still holding
        )
    
    return dp[0][0]  # start from day 0, not holding
```

**Why n+2 size?**
- We need `dp[i+2]` when `i = n-1`, so we allocate `n+2` slots
- `dp[n]` and `dp[n+1]` remain 0 (no profit after we run out of days)

**Trace through Example 1: `prices = [1,2,3,0,2]`**

| i   | prices[i] | dp[i][0] | dp[i][1] | Reasoning |
|-----|-----------|----------|----------|-----------|
| 5   | N/A       | 0        | 0        | Base case |
| 4   | N/A       | 0        | 0        | Base case |
| 4   | 2         | max(-2+0, 0) = 0 | max(2+0, 0) = 2 | Day 4: can buy or sell |
| 3   | 0         | max(-0+2, 0) = 2 | max(0+0, 2) = 2 | Day 3: buying benefits us |
| 2   | 3         | max(-3+2, 2) = 2 | max(3+0, 2) = 3 | Day 2: sell here is good |
| 1   | 2         | max(-2+3, 2) = 3 | max(2+2, 3) = 4 | Day 1: complex state |
| 0   | 1         | max(-1+4, 3) = 3 | max(1+0, 4) = 4 | Day 0: answer is dp[0][0] = 3 |

**Complexity Analysis:**
- **Time**: O(n) - we visit each day once
- **Space**: O(n) - DP table of size `n+2` (or O(1) if space-optimized to keep only 3 rows)

## Space Optimization

Since `dp[i]` only depends on `dp[i+1]` and `dp[i+2]`, we can use only 3 variables:

```python
def maxProfit(prices):
    if not prices:
        return 0
    
    not_hold_2, not_hold_1 = 0, 0  # dp[i+2][0], dp[i+1][0]
    hold_1 = 0                       # dp[i+1][1]
    
    for i in range(len(prices) - 1, -1, -1):
        not_hold = max(-prices[i] + hold_1, not_hold_1)
        hold = max(prices[i] + not_hold_2, hold_1)
        
        # Shift for next iteration
        not_hold_2 = not_hold_1
        not_hold_1 = not_hold
        hold_1 = hold
    
    return not_hold_1
```

**Space Complexity**: O(1)

# Tags
- Dynamic Programming
- State Machine (hold/not-hold)
- Cooldown constraint
- Multiple transactions

