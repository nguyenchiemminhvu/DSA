## Problem

https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

```
You are given an integer array prices where prices[i] is the price of a given stock on the ith day.

On each day, you may decide to buy and/or sell the stock. You can only hold at most one share of the stock at any time. However, you can sell and buy the stock multiple times on the same day, ensuring you never hold more than one share of the stock.

Find and return the maximum profit you can achieve.

Example 1:

Input: prices = [7,1,5,3,6,4]
Output: 7
Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
Total profit is 4 + 3 = 7.

Example 2:

Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Total profit is 4.

Example 3:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: There is no way to make a positive profit, so we never buy the stock to achieve the maximum profit of 0.

Constraints:

1 <= prices.length <= 3 * 104
0 <= prices[i] <= 104
 
```

## Observations

1. **Multiple transactions allowed**: Unlike the first version of this problem, we can buy and sell multiple times, which means we can capture every profitable opportunity.

2. **Key insight**: To maximize profit, we should capture every positive price difference between consecutive days. If the price goes up from day i to day i+1, we should "buy" on day i and "sell" on day i+1.

3. **Greedy approach works**: Since we can perform unlimited transactions, we don't need to worry about timing or holding periods. We can simply accumulate all positive daily gains.

4. **Edge cases**: 
   - If prices are strictly decreasing, we make no transactions (profit = 0)
   - If prices are strictly increasing, we buy on first day and sell on last day
   - Mixed patterns: we capture each upward movement

5. **Mathematical insight**: The maximum profit equals the sum of all positive differences between consecutive days.

## Solution

1. **Iterate through consecutive days**: Start from day 1 and compare with the previous day.

2. **Calculate daily difference**: For each day i, compute `diff = prices[i] - prices[i-1]`.

3. **Accumulate positive gains**: If the difference is positive (price increased), add it to the result. If negative or zero, ignore it.

4. **Return total profit**: The sum of all positive differences gives us the maximum possible profit.

**Why this works:**
- When price increases from day i-1 to day i, we can buy on day i-1 and sell on day i to capture the profit.
- Since we can buy and sell on the same day, we can chain these transactions to capture every upward price movement.
- This greedy approach is optimal because we're not missing any profitable opportunities.

**Time Complexity:** O(n) - single pass through the array
**Space Complexity:** O(1) - only using constant extra space

**Example walkthrough with [7,1,5,3,6,4]:**
- Day 1→2: 1-7 = -6 (ignore)
- Day 2→3: 5-1 = +4 (add to result)
- Day 3→4: 3-5 = -2 (ignore)  
- Day 4→5: 6-3 = +3 (add to result)
- Day 5→6: 4-6 = -2 (ignore)
- Total profit: 4 + 3 = 7

## Tags

array, greedy