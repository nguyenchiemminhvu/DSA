## Problem

https://leetcode.com/problems/delete-and-earn/description

You are given an integer array `nums`. You want to maximize the number of points you get by performing the following operation any number of times:

1. Pick any `nums[i]` and delete it to earn `nums[i]` points
2. Afterwards, you must delete every element equal to `nums[i] - 1` and every element equal to `nums[i] + 1`

Return the maximum number of points you can earn by applying the above operation some number of times.

**Example 1:**
- Input: `nums = [3,4,2]`
- Output: `6`
- Explanation: Delete 4 (earn 4 points, 3 is deleted) → Delete 2 (earn 2 points). Total = 6 points.

**Example 2:**
- Input: `nums = [2,2,3,3,3,4]`
- Output: `9`
- Explanation: Delete three 3's (earn 3+3+3 = 9 points, all 2's and 4's are deleted). Total = 9 points.

**Constraints:**
- 1 ≤ nums.length ≤ 2 × 10⁴
- 1 ≤ nums[i] ≤ 10⁴

## Observations

1. **Key Insight - Aggregate by Value**: If we decide to take a number `i`, we can take ALL occurrences of `i` since deleting one `i` deletes all adjacent values. So we should sum up all occurrences of each number.

2. **Transformation to House Robber**: This problem becomes similar to the "House Robber" problem:
   - Create a sum array where `sum[i]` = total points we get if we take all occurrences of number `i`
   - We can't take adjacent numbers (i and i+1)
   - We want to maximize the total points
   - This is the classic dynamic programming "House Robber" pattern

3. **Optimal Substructure**: For each number `i`, we have two choices:
   - Take all occurrences of `i`: earn `sum[i] + dp[i-2]` (can't take i-1)
   - Skip `i`: earn `dp[i-1]` (can take i-1 or earlier)

4. **Space Optimization**: We only need `dp[i-1]` and `dp[i-2]` to compute `dp[i]`, but for clarity, we use an array approach.

## Solution

### Approach 1: Top-Down DP with Memoization

```python
class Solution:
    def deleteAndEarn(self, nums: List[int]) -> int:
        max_val = max(nums)
        
        # Sum all occurrences of each number
        s = defaultdict(int)
        for val in nums:
            s[val] += val
        
        # Memoized recursion
        mem = {}
        def F(i: int) -> int:
            if i <= 0:
                return 0
            if i in mem:
                return mem[i]
            res = max(
                s[i] + F(i - 2),    # Take all i's (skip i-1)
                F(i - 1)             # Skip i
            )
            mem[i] = res
            return res
        
        return F(max_val)
```

**Time Complexity**: O(n + max_val) - O(n) to build the sum dictionary, O(max_val) for DP states
**Space Complexity**: O(max_val) - memoization dictionary and recursion stack

### Approach 2: Bottom-Up DP (Preferred)

```python
class Solution:
    def deleteAndEarn(self, nums: List[int]) -> int:
        max_val = max(nums)
        
        # Sum all occurrences of each number
        s = defaultdict(int)
        for val in nums:
            s[val] += val
        
        # Bottom-up DP
        dp = [0] * (max_val + 1)
        for i in range(1, max_val + 1):
            dp[i] = max(
                dp[i - 1],                      # Skip number i
                s[i] + (dp[i - 2] if i >= 2 else 0)  # Take all i's
            )
        
        return dp[max_val]
```

**Time Complexity**: O(n + max_val)
**Space Complexity**: O(max_val) for the DP array

### Approach 3: Space-Optimized DP

```python
class Solution:
    def deleteAndEarn(self, nums: List[int]) -> int:
        max_val = max(nums)
        
        # Sum all occurrences of each number
        s = defaultdict(int)
        for val in nums:
            s[val] += val
        
        # Only keep track of previous two states
        prev2, prev1 = 0, 0
        
        for i in range(1, max_val + 1):
            current = max(prev1, s[i] + prev2)
            prev2, prev1 = prev1, current
        
        return prev1
```

**Time Complexity**: O(n + max_val)
**Space Complexity**: O(max_val) for the sum dictionary, O(1) for DP variables

## Walkthrough - Example 2: [2,2,3,3,3,4]

1. **Build sum array**:
   - `s[2] = 2+2 = 4`
   - `s[3] = 3+3+3 = 9`
   - `s[4] = 4`

2. **DP transitions** (max_val = 4):
   - `dp[0] = 0`
   - `dp[1] = max(dp[0], s[1] + 0) = max(0, 0) = 0`
   - `dp[2] = max(dp[1], s[2] + dp[0]) = max(0, 4 + 0) = 4`
   - `dp[3] = max(dp[2], s[3] + dp[1]) = max(4, 9 + 0) = 9`
   - `dp[4] = max(dp[3], s[4] + dp[2]) = max(9, 4 + 4) = 9`

3. **Answer**: `dp[4] = 9`

# Tags

#DynamicProgramming #HouseRobber #GreedyDP #Aggregation

