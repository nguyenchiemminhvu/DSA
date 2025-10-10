## Problem

https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

```
You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

Example 1:

Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

Example 2:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.

Constraints:

1 <= prices.length <= 105
0 <= prices[i] <= 104
```

## Observations

1. **Single Transaction Rule**: We can only buy once and sell once, and we must buy before we sell.

2. **Maximum Profit Goal**: We want to find the maximum difference between a selling price and a buying price, where the selling day comes after the buying day.

3. **Greedy Approach**: At each day, we want to know:
   - What's the minimum price we've seen so far (best buying opportunity)
   - What's the maximum profit we can achieve if we sell today

4. **Edge Cases**:
   - If prices only decrease, no profit can be made (return 0)
   - Single day: no transaction possible (return 0)
   - All prices are the same: no profit (return 0)

5. **Key Insight**: We don't need to track which specific days to buy/sell, just the minimum price seen so far and maximum profit achievable.

## Solution

**Algorithm: Single Pass with Running Minimum**

The solution uses a greedy approach that processes the array in a single pass:

**How it works:**

1. **Initialize**: 
   - `cur_min = 0xFFFFFFFF` (maximum 32-bit value, ensures any price will be smaller)
   - `max_profit = 0`

2. **For each price**:
   - Calculate potential profit: `val - cur_min`
   - Update `max_profit` if this profit is better
   - Update `cur_min` if current price is lower (better buying opportunity)

3. **Return**: `max(0, max_profit)` ensures we never return negative profit

**Example Walkthrough** (prices = [7,1,5,3,6,4]):

| Day | Price | cur_min | val - cur_min | max_profit |
|-----|-------|---------|---------------|------------|
| 0   | 7     | 7       | 0             | 0          |
| 1   | 1     | 1       | 0             | 0          |
| 2   | 5     | 1       | 4             | 4          |
| 3   | 3     | 1       | 2             | 4          |
| 4   | 6     | 1       | 5             | 5          |
| 5   | 4     | 1       | 3             | 5          |

Result: 5 (buy at price 1, sell at price 6)

**Time Complexity**: O(n) - single pass through the array
**Space Complexity**: O(1) - only using constant extra space

**Alternative Approaches**:
1. **Brute Force**: O(n²) - check all pairs of buy/sell days
2. **Dynamic Programming**: O(n) time, O(n) space - track max profit up to each day
3. **This Solution**: O(n) time, O(1) space - optimal greedy approach

## Tags

array, greedy