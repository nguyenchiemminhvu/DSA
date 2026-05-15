## Problem

https://leetcode.com/problems/minimum-cost-for-tickets/description/

You have planned some train traveling one year in advance. The days of the year in which you will travel are given as an integer array `days`. Each day is an integer from 1 to 365.

Train tickets are sold in three different ways:
- A 1-day pass is sold for `costs[0]` dollars
- A 7-day pass is sold for `costs[1]` dollars
- A 30-day pass is sold for `costs[2]` dollars

The passes allow that many days of consecutive travel. For example, if you get a 7-day pass on day 2, you can travel for 7 days: 2, 3, 4, 5, 6, 7, and 8.

**Return the minimum number of dollars you need to travel every day in the given list of days.**

### Examples

**Example 1:**
- Input: `days = [1,4,6,7,8,20]`, `costs = [2,7,15]`
- Output: `11`
- Explanation: Buy a 1-day pass on day 1 ($2), a 7-day pass on day 4 ($7), and a 1-day pass on day 20 ($2). Total: $11.

**Example 2:**
- Input: `days = [1,2,3,4,5,6,7,8,9,10,30,31]`, `costs = [2,7,15]`
- Output: `17`
- Explanation: Buy a 30-day pass on day 1 ($15) covering days 1-30, and a 1-day pass on day 31 ($2). Total: $17.

### Constraints
- $1 \le \text{days.length} \le 365$
- $1 \le \text{days}[i] \le 365$
- `days` is in strictly increasing order
- `costs.length == 3`
- $1 \le \text{costs}[i] \le 1000$

## Observations

1. **Only Travel Days Matter**: We only need to purchase tickets to cover the specific days we travel. Days in between don't incur costs.

2. **Overlapping Coverage**: When we buy a pass on a certain day, it covers multiple consecutive days. We need to find the optimal combination of passes to minimize total cost.

3. **Decision Point**: At each travel day, we have three choices:
   - Buy a 1-day pass (covers today)
   - Buy a 7-day pass (covers the next 7 days)
   - Buy a 30-day pass (covers the next 30 days)

4. **Subproblem Structure**: The problem exhibits optimal substructure - the minimum cost to cover day $i$ depends on the minimum cost to cover previous days. This suggests a dynamic programming approach.

5. **State Representation**: We can represent the state as:
   - The current day index (which travel day we're considering)
   - OR the current calendar day (1 to 365)
   
   Both approaches work, but they have different trade-offs in complexity.

6. **Greedy Won't Work**: We can't simply choose the pass with the best "cost per day" ratio because future travel patterns matter. Sometimes a more expensive pass early on saves more money overall.

## Solution

### Approach: Dynamic Programming (Bottom-Up)

The optimal solution uses **1D dynamic programming** over all 365 days of the year.

**State Definition:**
- `dp[i]` = minimum cost to cover all travel days from day 1 to day $i$

**Key Insight:** For each day from 1 to 365, we either:
1. Don't travel that day → carry forward the previous cost
2. Travel that day → choose the minimum cost among three options:
   - Buy a 1-day pass: `costs[0] + dp[i-1]`
   - Buy a 7-day pass: `costs[1] + dp[i-7]`
   - Buy a 30-day pass: `costs[2] + dp[i-30]`

**Algorithm:**

```python
class Solution:
    def mincostTickets(self, days: List[int], costs: List[int]) -> int:
        n = len(days)
        s_days = set(days)  # Convert to set for O(1) lookup
        
        # dp[i] = minimum cost to cover all days up to day i
        dp = [float('inf') for _ in range(366)]
        dp[0] = 0
        
        for i in range(1, 366):
            if i not in s_days:
                # No travel on day i, carry forward previous cost
                dp[i] = dp[i - 1]
            else:
                # Travel on day i, choose minimum among three options
                dp[i] = min(
                    costs[0] + dp[i - 1],      # 1-day pass
                    costs[1] + dp[i - 7] if i >= 7 else costs[1],      # 7-day pass
                    costs[2] + dp[i - 30] if i >= 30 else costs[2]     # 30-day pass
                )
        
        return dp[365]
```

**Time Complexity:** $O(365) = O(1)$ - We iterate through all 365 days exactly once.

**Space Complexity:** $O(365) = O(1)$ - The DP array has fixed size.

### Alternative Approach: Top-Down with Travel Days

Instead of iterating through all 365 days, we can process only the travel days:

```python
def mincostTickets(self, days: List[int], costs: List[int]) -> int:
    s_days = set(days)
    memo = {}
    
    def dp(i: int) -> int:
        """Minimum cost starting from day i (calendar day)"""
        if i <= 0:
            return 0
        if i in memo:
            return memo[i]
        
        if i not in s_days:
            # Don't travel on day i
            res = dp(i - 1)
        else:
            # Travel on day i, choose minimum
            res = min(
                costs[0] + dp(i - 1),
                costs[1] + dp(i - 7),
                costs[2] + dp(i - 30)
            )
        
        memo[i] = res
        return res
    
    return dp(365)
```

### Why This Works

The DP solution works because:
1. We consider every possible day (1-365)
2. For days without travel, we inherit the previous cost (no new purchase needed)
3. For days with travel, we must have a valid pass. We choose which pass to buy based on three local decisions, each leading to an optimal subproblem
4. The minimum cost at day 365 represents the optimal solution for all travel days

### Example Walkthrough

For `days = [1,4,6,7,8,20]`, `costs = [2,7,15]`:

| Day | Travel? | Option 1 | Option 2 | Option 3 | dp[i] |
|-----|---------|----------|----------|----------|-------|
| 0   | N       | -        | -        | -        | 0     |
| 1   | Y       | 2+0=2    | 7+0=7    | 15+0=15  | 2     |
| 2   | N       | -        | -        | -        | 2     |
| 3   | N       | -        | -        | -        | 2     |
| 4   | Y       | 2+2=4    | 7+0=7    | 15+0=15  | 4     |
| 5   | N       | -        | -        | -        | 4     |
| 6   | Y       | 2+4=6    | 7+2=9    | 15+0=15  | 6     |
| 7   | Y       | 2+6=8    | 7+2=9    | 15+0=15  | 8     |
| 8   | Y       | 2+8=10   | 7+4=11   | 15+0=15  | 10    |
| ... | ... | ... | ... | ... | ... |
| 20  | Y       | 2+9=11   | 7+...    | 15+...   | 11    |

# Tags

dynamic-programming, optimization, day-pass-planning

