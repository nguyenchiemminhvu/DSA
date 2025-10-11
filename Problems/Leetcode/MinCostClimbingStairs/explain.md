## Problem

https://leetcode.com/problems/min-cost-climbing-stairs/

```
You are given an integer array cost where cost[i] is the cost of ith step on a staircase. Once you pay the cost, you can either climb one or two steps.

You can either start from the step with index 0, or the step with index 1.

Return the minimum cost to reach the top of the floor.

Example 1:

Input: cost = [10,15,20]
Output: 15
Explanation: You will start at index 1.
- Pay 15 and climb two steps to reach the top.
The total cost is 15.

Example 2:

Input: cost = [1,100,1,1,1,100,1,1,100,1]
Output: 6
Explanation: You will start at index 0.
- Pay 1 and climb two steps to reach index 2.
- Pay 1 and climb two steps to reach index 4.
- Pay 1 and climb two steps to reach index 6.
- Pay 1 and climb one step to reach index 7.
- Pay 1 and climb two steps to reach index 9.
- Pay 1 and climb one step to reach the top.
The total cost is 6.

Constraints:

2 <= cost.length <= 1000
0 <= cost[i] <= 999
```

## Observations

1. **Problem Understanding**: 
   - We have a staircase with costs associated with each step
   - We can start from either step 0 or step 1 (both are free initially)
   - From any step, we can climb either 1 or 2 steps forward
   - Goal: Find minimum cost to reach the "top" (beyond the last step)

2. **Key Insights**:
   - This is a classic dynamic programming problem
   - At each step, we have a choice: climb 1 step or climb 2 steps
   - We want to minimize the total cost, so we choose the cheaper option
   - The "top" means reaching index `n` (one step beyond the last element)

3. **State Definition**:
   - `dp[i]` = minimum cost to reach the top starting from step `i`
   - Base case: `dp[i] = 0` when `i >= n` (already at or past the top)

4. **Recurrence Relation**:
   - `dp[i] = cost[i] + min(dp[i+1], dp[i+2])`
   - We pay the cost of current step, then choose the cheaper path forward

5. **Starting Points**:
   - We can start from either step 0 or step 1
   - Answer is `min(dp[0], dp[1])`

## Solution

The solution implements both memoized recursion and bottom-up dynamic programming approaches:

### Approach 1: Memoized Recursion (Top-Down DP)
```python
def F(i: int) -> int:
    if i >= n:
        return 0  # Already at the top
    if i in memo:
        return memo[i]
    # Pay cost[i] and choose minimum of next two options
    memo[i] = min(cost[i] + F(i + 1), cost[i] + F(i + 2))
    return memo[i]
```

### Approach 2: Bottom-Up DP (Iterative)
```python
def DP(i: int) -> int:
    dp = [0] * (n + 2)  # Extra space for indices n and n+1
    # Fill from right to left (bottom-up)
    for j in range(n - 1, -1, -1):
        dp[j] = min(cost[j] + dp[j + 1], cost[j] + dp[j + 2])
    return dp[i]
```

### Time & Space Complexity:
- **Time**: O(n) - we visit each step once
- **Space**: O(n) - for memoization/dp array

### Step-by-step Example:
For `cost = [1,100,1,1,1,100,1,1,100,1]`:

Working backwards:
- `dp[10] = dp[11] = 0` (past the end)
- `dp[9] = 1 + min(0, 0) = 1`
- `dp[8] = 100 + min(1, 0) = 100`
- `dp[7] = 1 + min(100, 1) = 2`
- `dp[6] = 1 + min(2, 100) = 3`
- `dp[5] = 100 + min(3, 2) = 102`
- `dp[4] = 1 + min(102, 3) = 4`
- `dp[3] = 1 + min(4, 102) = 5`
- `dp[2] = 1 + min(5, 4) = 5`
- `dp[1] = 100 + min(5, 5) = 105`
- `dp[0] = 1 + min(105, 5) = 6`

Answer: `min(dp[0], dp[1]) = min(6, 105) = 6`

## Tags

array, dynamic programming