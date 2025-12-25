## Problem

https://leetcode.com/problems/jump-game-vi/

You are given a 0-indexed integer array `nums` and an integer `k`.

You are initially standing at index 0. In one move, you can jump at most `k` steps forward without going outside the boundaries of the array. That is, you can jump from index `i` to any index in the range `[i + 1, min(n - 1, i + k)]` inclusive.

You want to reach the last index of the array (index `n - 1`). Your score is the sum of all `nums[j]` for each index `j` you visited in the array.

Return the maximum score you can get.

**Example 1:**
```
Input: nums = [1,-1,-2,4,-7,3], k = 2
Output: 7
Explanation: You can choose your jumps forming the subsequence [1,-1,4,3]. The sum is 7.
```

**Example 2:**
```
Input: nums = [10,-5,-2,4,0,3], k = 3
Output: 17
Explanation: You can choose your jumps forming the subsequence [10,4,3]. The sum is 17.
```

**Example 3:**
```
Input: nums = [1,-5,-20,4,-1,3,-6,-3], k = 2
Output: 0
```

**Constraints:**
- `1 <= nums.length, k <= 10^5`
- `-10^4 <= nums[i] <= 10^4`

## Observations

1. **Dynamic Programming Problem**: We need to find the maximum score to reach the last index
2. **State Definition**: `dp[i]` = maximum score to reach index `i` from index 0
3. **Recurrence Relation**: `dp[i] = nums[i] + max(dp[j])` where `j` is in range `[max(0, i-k), i-1]`
4. **Base Case**: `dp[0] = nums[0]`
5. **The Bottleneck**: The naive DP solution is O(n*k) because for each position we check up to k previous positions to find the maximum. This causes **TLE** when n and k are large (up to 10^5)
6. **Key Insight**: We need to efficiently find the maximum value in a sliding window of size k. This is a classic **Sliding Window Maximum** problem!

## Solution

### Approach 1: Naive DP (TLE) - O(n*k)

```python
class Solution:
    def maxResult(self, nums: List[int], k: int) -> int:
        n = len(nums)
        dp = [float('-inf')] * n
        dp[0] = nums[0]
        
        for i in range(1, n):
            # Check all positions we can jump from (within k steps back)
            for j in range(max(0, i - k), i):
                dp[i] = max(dp[i], dp[j] + nums[i])
        
        return dp[-1]
```

**Why TLE?** For each position i, we iterate through up to k previous positions. This gives O(n*k) complexity which is too slow when both n and k are 10^5 (10^10 operations).

### Approach 2: Monotonic Deque (Optimal) - O(n)

Use a **monotonic decreasing deque** to maintain the indices of potential maximum values in the sliding window.

**Key Ideas:**
- Deque stores indices (not values) in decreasing order of their dp values
- Front of deque always contains the index with maximum dp value in current window
- Remove indices from front if they're out of the k-step window
- Remove indices from back if their dp values are smaller than current (they'll never be used)

```python
from collections import deque

class Solution:
    def maxResult(self, nums: List[int], k: int) -> int:
        n = len(nums)
        dp = [0] * n
        dp[0] = nums[0]
        
        # Deque stores indices, maintains decreasing order of dp values
        dq = deque([0])
        
        for i in range(1, n):
            # Remove indices outside the window [i-k, i-1]
            while dq and dq[0] < i - k:
                dq.popleft()
            
            # The front has the maximum dp value in the window
            dp[i] = nums[i] + dp[dq[0]]
            
            # Maintain monotonic decreasing order
            # Remove indices with smaller dp values (they won't be useful)
            while dq and dp[dq[-1]] <= dp[i]:
                dq.pop()
            
            dq.append(i)
        
        return dp[-1]
```

**Complexity:**
- Time: O(n) - each index is added and removed from deque at most once
- Space: O(n) for dp array, O(k) for deque

### Approach 3: Priority Queue (Heap) - O(n log n)

Another approach using a max heap to track the maximum dp value in the window.

```python
import heapq

class Solution:
    def maxResult(self, nums: List[int], k: int) -> int:
        n = len(nums)
        dp = [0] * n
        dp[0] = nums[0]
        
        # Max heap: (-dp_value, index)
        heap = [(-nums[0], 0)]
        
        for i in range(1, n):
            # Remove indices outside the window
            while heap and heap[0][1] < i - k:
                heapq.heappop(heap)
            
            # Get maximum from valid indices
            dp[i] = nums[i] - heap[0][0]
            
            # Add current index to heap
            heapq.heappush(heap, (-dp[i], i))
        
        return dp[-1]
```

**Complexity:**
- Time: O(n log n) - heap operations are O(log n)
- Space: O(n)

**Comparison:**
- Monotonic Deque is optimal with O(n) time
- Heap solution is easier to implement but slightly slower O(n log n)
- Both pass the time constraints, but deque is preferred

# Tags
`Dynamic Programming` `Sliding Window Maximum` `Monotonic Deque` `Priority Queue` `Array`

