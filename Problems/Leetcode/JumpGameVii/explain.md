## Problem

https://leetcode.com/problems/jump-game-vii/description

Given a 0-indexed binary string `s` and two integers `minJump` and `maxJump`, determine if you can reach the last index of the string.

**Rules:**
- Start at index 0 (which is always '0')
- From index `i`, you can jump to index `j` if:
  - `i + minJump <= j <= min(i + maxJump, s.length - 1)`
  - `s[j] == '0'`
- Return `True` if you can reach `s.length - 1`, otherwise `False`

**Example 1:**
```
Input: s = "011010", minJump = 2, maxJump = 3
Output: true
Explanation:
  - Jump from index 0 to index 3 (distance = 3)
  - Jump from index 3 to index 5 (distance = 2)
```

**Example 2:**
```
Input: s = "01101110", minJump = 2, maxJump = 3
Output: false
Explanation: Cannot reach the last index within the jump constraints
```

**Constraints:**
- `2 <= s.length <= 10^5`
- `s[i]` is either '0' or '1'
- `s[0] == '0'`
- `1 <= minJump <= maxJump < s.length`

## Observations

1. **Reachability Definition**: `dp[i] = True` means we can reach index `i` starting from index 0.

2. **Base Case**: `dp[0] = True` (we start at index 0).

3. **Transition Logic**: For position `i`, we need to check if ANY position `j` in the valid range can reach us:
   - Valid range: `[i - maxJump, i - minJump]`
   - Condition: `s[j] == '0'` and `dp[j] == True`

4. **Naive DP is Slow**: The straightforward approach would check all positions in the valid range for each index, resulting in **O(n × (maxJump - minJump))** time complexity, which can be up to **O(n²)**.

5. **Key Optimization**: Use a **sliding window with prefix sum** technique:
   - Maintain `count` = number of reachable positions in the current valid range
   - When we move to position `i`:
     - **Add** the position `i - minJump` (entering the valid range from the right)
     - **Remove** the position `i - maxJump - 1` (exiting the valid range from the left)
   - If `count > 0` and `s[i] == '0'`, then `dp[i] = True`

6. **Target Check**: If `s[n-1] == '1'`, return `False` immediately (we can never land on '1').

7. **Time Complexity**: O(n) - single pass through the string with O(1) operations per index.

## Solution

### Approach: Sliding Window with Counting

The solution uses dynamic programming combined with a sliding window technique to efficiently count reachable positions:

```python
class Solution:
    def canReach(self, s: str, min_jump: int, max_jump: int) -> bool:
        n = len(s)
        
        # Quick check: if the last character is '1', we can never reach it
        if s[-1] == '1':
            return False
        
        dp = [False] * n
        dp[0] = True  # Base case: we start at index 0
        count = 0     # Count of reachable positions in the valid range
        
        for i in range(1, n):
            # Add position (i - min_jump) to the count when it enters the valid range
            r = i - min_jump
            if r >= 0 and dp[r] == True:
                count += 1
            
            # Remove position (i - max_jump - 1) when it exits the valid range
            l = i - max_jump - 1
            if l >= 0 and dp[l] == True:
                count -= 1
            
            # If there's at least one reachable position in range and s[i] is '0'
            if s[i] == '0' and count > 0:
                dp[i] = True
        
        return dp[n - 1]
```

### Step-by-step Walkthrough (Example 1: s = "011010", minJump = 2, maxJump = 3)

```
Index:  0  1  2  3  4  5
Char:   0  1  1  0  1  0
        
Initial: dp = [T, F, F, F, F, F], count = 0

i=1: s[1]='1'
  - r = 1-2 = -1 (no add)
  - l = 1-3-1 = -3 (no remove)
  - count = 0, s[1]='1' → dp[1] = F

i=2: s[2]='1'
  - r = 2-2 = 0, dp[0]=T → count = 1
  - l = 2-3-1 = -2 (no remove)
  - count = 1, but s[2]='1' → dp[2] = F

i=3: s[3]='0'
  - r = 3-2 = 1, dp[1]=F (no add)
  - l = 3-3-1 = -1 (no remove)
  - count = 1, s[3]='0' → dp[3] = T ✓

i=4: s[4]='1'
  - r = 4-2 = 2, dp[2]=F (no add)
  - l = 4-3-1 = 0, dp[0]=T → count = 0
  - count = 0, s[4]='1' → dp[4] = F

i=5: s[5]='0'
  - r = 5-2 = 3, dp[3]=T → count = 1
  - l = 5-3-1 = 1, dp[1]=F (no remove)
  - count = 1, s[5]='0' → dp[5] = T ✓

Return: dp[5] = True
```

### Intuition Behind the Sliding Window

For each position `i`, the **valid jump sources** are in range `[i - maxJump, i - minJump]`. As `i` increases:
- Positions to the left of `i - maxJump` become out of range (remove them)
- Positions between `i - maxJump` and `i - minJump` are in range (add when they enter)

By maintaining a running count of reachable positions in the valid range, we avoid the O(maxJump) iteration per position.

## Tags

- Dynamic Programming
- Sliding Window
- Range Sum / Prefix Sum
- Greedy Optimization

