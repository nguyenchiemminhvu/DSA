## Problem

https://leetcode.com/problems/jump-game-ii/

```
You are given a 0-indexed array of integers nums of length n. You are initially positioned at index 0.

Each element nums[i] represents the maximum length of a forward jump from index i. In other words, if you are at index i, you can jump to any index (i + j) where:

0 <= j <= nums[i] and
i + j < n
Return the minimum number of jumps to reach index n - 1. The test cases are generated such that you can reach index n - 1.

Example 1:

Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:

Input: nums = [2,3,0,1,4]
Output: 2

Constraints:

1 <= nums.length <= 104
0 <= nums[i] <= 1000
It's guaranteed that you can reach nums[n - 1].
```

## Observations

1. **Problem Understanding**: We need to find the **minimum number of jumps** to reach the last index, starting from index 0. This is different from Jump Game I where we only needed to determine if it's possible to reach the end.

2. **Dynamic Programming State Definition**: Let `F(i)` represent the minimum number of jumps needed to reach index `i` from index 0.

3. **Base Case**: `F(0) = 0` since we're already at the starting position.

4. **Recurrence Relation**: For any index `i`, we can reach it from any previous index `j` where `j + nums[j] >= i`. So:
   ```
   F(i) = min(F(j) + 1) for all valid j where j < i and j + nums[j] >= i
   ```

5. **Search Strategy**: The solution uses a **backwards search** approach - for each position `i`, it looks at all previous positions `j` that can reach `i` and takes the minimum.

6. **Memoization**: The recursive solution uses memoization to avoid recomputing the same subproblems, which is crucial for efficiency.

7. **Guaranteed Solution**: The problem states that it's guaranteed we can reach the last index, so we don't need to handle impossible cases.

## Solution

### Approach 1: Top-Down Dynamic Programming (Memoization)

The provided solution uses a **recursive approach with memoization**:

```python
class Solution:
    def jump(self, nums: List[int]) -> int:
        INF = 0x7FFFFFFF
        n = len(nums)
        memo = {}

        def F(i: int) -> int:
            if i <= 0:
                return 0
            
            if i in memo:
                return memo[i]
            
            min_jump = INF
            for j in range(i - 1, -1, -1):
                if j + nums[j] >= i:
                    min_at_j = F(j)
                    if min_at_j != INF:
                        min_jump = min(min_jump, 1 + min_at_j)
            memo[i] = min_jump
            return memo[i]
        
        return F(n - 1)
```

**How it works:**
1. **Base Case**: If `i <= 0`, return 0 (no jumps needed to reach the start)
2. **Memoization Check**: If we've already computed `F(i)`, return the cached result
3. **Backwards Search**: For each position `j` from `i-1` down to 0:
   - Check if position `j` can reach position `i` (i.e., `j + nums[j] >= i`)
   - If yes, recursively compute the minimum jumps to reach `j`
   - Take the minimum among all valid paths: `1 + F(j)`
4. **Cache and Return**: Store the result in memo and return it

**Time Complexity**: O(n²) - for each position, we might check all previous positions
**Space Complexity**: O(n) - for the memoization table and recursion stack

### Approach 2: Bottom-Up Dynamic Programming (Tabulation)

A more efficient approach would be to use **tabulation** (bottom-up DP):

```python
def jump_tabulation(nums: List[int]) -> int:
    n = len(nums)
    if n <= 1:
        return 0
    
    # dp[i] represents minimum jumps to reach index i
    dp = [float('inf')] * n
    dp[0] = 0  # Base case: 0 jumps to reach index 0
    
    for i in range(n):
        if dp[i] == float('inf'):
            continue  # Can't reach this position
            
        # From position i, try all possible jumps
        max_jump = min(i + nums[i], n - 1)
        for j in range(i + 1, max_jump + 1):
            dp[j] = min(dp[j], dp[i] + 1)
    
    return dp[n - 1]
```

**Advantages of Tabulation:**
1. **Forward Direction**: More intuitive - we build solutions from smaller to larger indices
2. **Better Space Efficiency**: No recursion stack overhead
3. **Cache-Friendly**: Sequential access pattern
4. **Easier to Optimize**: Can potentially reduce space complexity further

**How Tabulation Works:**
1. Initialize `dp[0] = 0` and all other positions to infinity
2. For each reachable position `i`, try all possible jumps from that position
3. Update `dp[j]` for all positions `j` that can be reached from `i`
4. The answer is `dp[n-1]`

### Approach 3: Greedy (Optimal)

For even better performance, a **greedy approach** can solve this in O(n) time:

```python
def jump_greedy(nums: List[int]) -> int:
    n = len(nums)
    if n <= 1:
        return 0
    
    jumps = 0
    current_end = 0      # Farthest we can reach with current number of jumps
    farthest = 0         # Farthest we can reach overall
    
    for i in range(n - 1):
        farthest = max(farthest, i + nums[i])
        
        if i == current_end:  # Need to make another jump
            jumps += 1
            current_end = farthest
    
    return jumps
```

**Key Insight**: At each step, we track the farthest position reachable with the current number of jumps. When we reach the boundary of what's possible with the current number of jumps, we increment the jump count.

## Tags

array, dynamic programming, greedy