## Problem

https://leetcode.com/problems/climbing-stairs-ii/description

## Problem

https://leetcode.com/problems/climbing-stairs-ii/description

You are climbing a staircase with **n + 1 steps**, numbered from 0 to n.

You are also given a 1-indexed integer array `costs` of length n, where `costs[i]` is the cost of step i.

**Movement Rules:**
- From step i, you can jump only to step i + 1, i + 2, or i + 3
- The cost of jumping from step i to step j is defined as: `costs[j] + (j - i)²`

You start from step 0 with cost = 0.

**Return:** the minimum total cost to reach step n.

### Example 1:
```
Input: n = 4, costs = [1,2,3,4]
Output: 13
Explanation:
One optimal path is 0 → 1 → 2 → 4
Jump	Cost Calculation	          Cost
0 → 1	costs[1] + (1-0)² = 1 + 1   = 2
1 → 2	costs[2] + (2-1)² = 2 + 1   = 3
2 → 4	costs[4] + (4-2)² = 4 + 4   = 8
Total: 2 + 3 + 8 = 13
```

### Example 2:
```
Input: n = 4, costs = [5,1,6,2]
Output: 11
Explanation:
One optimal path is 0 → 2 → 4
Jump	Cost Calculation	          Cost
0 → 2	costs[2] + (2-0)² = 6 + 4   = 10
2 → 4	costs[4] + (4-2)² = 2 + 4   = 6
Total: 10 + 6 = 16

Wait, let me recalculate. Actually the problem states costs[2] = 6 (1-indexed)
0 → 2	costs[2] + (2-0)² = 6 + 4   = 10
2 → 4	costs[4] + (4-2)² = 2 + 4   = 6
Total: 10 + 6 = 16 (but expected is 11)

Let me check with 0-indexed: costs = [5,1,6,2] means costs[1]=5, costs[2]=1, costs[3]=6, costs[4]=2
0 → 2	costs[2] + (2-0)² = 1 + 4   = 5
2 → 4	costs[4] + (4-2)² = 2 + 4   = 6
Total: 5 + 6 = 11 ✓
```

### Example 3:
```
Input: n = 3, costs = [9,8,3]
Output: 12
Explanation:
The optimal path is 0 → 3
Jump	Cost Calculation	          Cost
0 → 3	costs[3] + (3-0)² = 3 + 9   = 12
Total: 12
```

**Constraints:**
- 1 <= n == costs.length <= 10⁵
- 1 <= costs[i] <= 10⁴

---

## Observations

1. **Dynamic Programming Problem**: This is a classic shortest path problem that can be solved with DP. We need to find the minimum cost to reach each step.

2. **State Definition**: Let `dp[i]` = minimum total cost to reach step i from step 0.

3. **Base Case**: `dp[0] = 0` (we start at step 0 with no cost)

4. **Transitions**: For each step i, we can reach it from three previous positions:
   - From step i-1: `dp[i] = min(dp[i], dp[i-1] + costs[i] + 1²)`
   - From step i-2: `dp[i] = min(dp[i], dp[i-2] + costs[i] + 2²)`
   - From step i-3: `dp[i] = min(dp[i], dp[i-3] + costs[i] + 3²)`
   
   The costs are: 1, 4, and 9 respectively.

5. **Array Indexing**: The solution prepends 0 to the costs array to make it easier to work with 1-indexed step numbers.

6. **Time Complexity**: O(n) - single pass through n steps
   
7. **Space Complexity**: O(n) - DP array of size n+1

---

## Solution

### Approach: Bottom-Up Dynamic Programming

The solution uses tabulation (bottom-up DP) to compute the minimum cost for each step iteratively.

**Key Insights:**
- We can only jump 1, 2, or 3 steps forward
- We compute costs for all steps sequentially from 0 to n
- For each step, we consider all possible previous positions we could have come from
- We track the minimum cost to reach each step

**Algorithm:**
1. Prepend 0 to costs array to align with step numbering
2. Create a DP array initialized with infinity values
3. Set `dp[0] = 0` as the starting point
4. For each step i from 0 to n:
   - Try jumping from i-1: `dp[i] = min(dp[i], dp[i-1] + costs[i] + 1)`
   - Try jumping from i-2: `dp[i] = min(dp[i], dp[i-2] + costs[i] + 4)`
   - Try jumping from i-3: `dp[i] = min(dp[i], dp[i-3] + costs[i] + 9)`
5. Return `dp[n]`

**Example Walkthrough (n=4, costs=[1,2,3,4]):**
```
After prepending: costs = [0, 1, 2, 3, 4]
Initial: dp = [0, ∞, ∞, ∞, ∞]

i=0: dp[0] = 0 (no updates possible)
i=1: dp[1] = dp[0] + costs[1] + 1 = 0 + 1 + 1 = 2
     dp = [0, 2, ∞, ∞, ∞]
i=2: dp[2] = min(dp[1] + costs[2] + 1, dp[0] + costs[2] + 4)
           = min(2 + 2 + 1, 0 + 2 + 4)
           = min(5, 6) = 5
     dp = [0, 2, 5, ∞, ∞]
i=3: dp[3] = min(dp[2] + costs[3] + 1, dp[1] + costs[3] + 4, dp[0] + costs[3] + 9)
           = min(5 + 3 + 1, 2 + 3 + 4, 0 + 3 + 9)
           = min(9, 9, 12) = 9
     dp = [0, 2, 5, 9, ∞]
i=4: dp[4] = min(dp[3] + costs[4] + 1, dp[2] + costs[4] + 4, dp[1] + costs[4] + 9)
           = min(9 + 4 + 1, 5 + 4 + 4, 2 + 4 + 9)
           = min(14, 13, 15) = 13
     dp = [0, 2, 5, 9, 13]

Result: dp[4] = 13 ✓
```

### Alternative Approach (Memoized Top-Down)

The commented code uses memoization (top-down DP):
- Start from step n and work backwards
- Memoize results to avoid recomputation
- Base case: F(0) = 0

Both approaches have the same time and space complexity, but tabulation is often preferred for its simplicity and cache locality.

# Tags
- Dynamic Programming
- Tabulation (Bottom-Up DP)
- Shortest Path
- Medium

## Observations

## Solution

# Tags

