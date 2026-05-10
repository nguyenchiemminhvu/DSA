## Problem

https://leetcode.com/problems/house-robber/description

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, but there's a constraint: adjacent houses have security systems connected and will automatically alert the police if two adjacent houses are broken into on the same night.

**Input:** An integer array `nums` representing the amount of money in each house.

**Output:** Return the maximum amount of money you can rob without robbing two adjacent houses.

**Constraints:**
- 1 ≤ nums.length ≤ 100
- 0 ≤ nums[i] ≤ 400

**Examples:**
- Input: `[1,2,3,1]` → Output: `4` (rob houses at indices 0 and 2: 1 + 3 = 4)
- Input: `[2,7,9,3,1]` → Output: `12` (rob houses at indices 0, 2, and 4: 2 + 9 + 1 = 12)

## Observations

1. **Optimal Substructure:** The problem exhibits optimal substructure. The maximum amount we can rob from house `i` onwards depends only on the maximum amounts we can rob from `i+1` and `i+2` onwards.

2. **Choice at Each Position:** At each house `i`, we have exactly two choices:
   - **Rob house i:** We get `nums[i]` + the maximum we can rob starting from house `i+2` (must skip adjacent house `i+1`)
   - **Skip house i:** We get the maximum we can rob starting from house `i+1`

3. **Recurrence Relation:** `dp[i] = max(nums[i] + dp[i+2], dp[i+1])`
   - This means the maximum money robbed up to house `i` is the maximum of robbing house `i` plus whatever we could rob from `i+2` onwards, or skipping house `i` and robbing optimally from `i+1` onwards.

4. **Base Cases:** 
   - Beyond the last house (i ≥ n): we can't rob anything, so the value is 0
   - We need to consider at least 2 positions beyond the array to safely handle the recurrence

5. **Direction:** Working backward from the last house simplifies implementation because we rely on values that have already been computed (dp[i+1] and dp[i+2]).

## Solution

The solution uses **tabulation (bottom-up dynamic programming)**:

```python
dp = [0] * (n + 2)
for i in range(n - 1, -1, -1):
    dp[i] = max(nums[i] + dp[i + 2], dp[i + 1])
return dp[0]
```

**How it works:**

1. **Initialize DP Array:** Create an array `dp` of size `n+2` with all zeros. The extra 2 positions handle the base cases:
   - `dp[n]` = 0 (no house to rob)
   - `dp[n+1]` = 0 (no house to rob)

2. **Fill DP Table Backward:** Iterate from the last house (`n-1`) down to the first house (`0`):
   - For each house `i`, compute `dp[i]` as the maximum of:
     - Robbing house `i`: `nums[i] + dp[i+2]` (get money from this house plus optimal from 2 houses ahead)
     - Not robbing house `i`: `dp[i+1]` (skip to next house and get optimal from there)

3. **Return Answer:** `dp[0]` contains the maximum amount we can rob starting from house 0, which is the answer for the entire street.

**Why this works:**

- By computing `dp[i]` from right to left, when we compute `dp[i]`, we've already computed the optimal solutions for `dp[i+1]` and `dp[i+2]`.
- The tabulation approach avoids recalculating the same subproblems (unlike naive recursion) and uses only O(n) extra space.

**Time Complexity:** O(n) — we iterate through the array once.

**Space Complexity:** O(n) — we use a DP array of size n+2.

**Alternative Approach (Space-Optimized):**
Since we only need the previous two values (`dp[i+1]` and `dp[i+2]`), we can optimize to O(1) space by using two variables instead of an array.

# Tags
dynamic-programming, tabulation, optimal-substructure

