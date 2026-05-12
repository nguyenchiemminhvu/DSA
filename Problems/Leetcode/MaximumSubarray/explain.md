## Problem

https://leetcode.com/problems/maximum-subarray/description

Given an integer array `nums`, find the subarray with the largest sum, and return its sum.

**Constraints:**
- 1 <= nums.length <= 10^5
- -10^4 <= nums[i] <= 10^4

**Examples:**

Example 1:
```
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.
```

Example 2:
```
Input: nums = [1]
Output: 1
Explanation: The subarray [1] has the largest sum 1.
```

Example 3:
```
Input: nums = [5,4,-1,7,8]
Output: 23
Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.
```

## Observations

1. **Brute Force Approach:** We could check all possible subarrays, which would take O(n²) or O(n³) time depending on implementation.

2. **Key Insight (Greedy/Dynamic Programming):** At each position, we need to decide: should we extend the current subarray or start a new one?
   - If the cumulative sum becomes negative, it's better to reset and start fresh from the next element (because adding a negative number would only decrease future sums).
   - If the cumulative sum is positive, it's worth keeping because it can contribute to future elements.

3. **Kadane's Algorithm:** This is an optimal greedy approach that:
   - Maintains `cur` as the maximum sum of subarray ending at the current position
   - Maintains `res` as the overall maximum sum found so far
   - For each element, decide: start fresh or extend the current subarray
   - Time Complexity: O(n) - single pass through the array
   - Space Complexity: O(1) - only using two variables

4. **Pattern Recognition:**
   - When `cur < 0`, resetting it makes sense because any negative prefix would only reduce future sums
   - We must compare with `res` after adding each element to capture the maximum

## Solution

**Approach: Kadane's Algorithm (Greedy)**

```python
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        res = float('-inf')  # Track the maximum sum seen so far
        cur = 0               # Track the cumulative sum ending at current position
        
        for val in nums:
            cur += val        # Add current element to running sum
            res = max(res, cur)  # Update max if current sum is larger
            
            if cur < 0:       # If sum becomes negative, reset to 0
                cur = 0       # (better to start fresh from next element)
        
        return res
```

**How It Works (with example [-2,1,-3,4,-1,2,1,-5,4]):**

```
Index | val | cur (before) | cur (after) | res (update)
------|-----|-------------|-------------|-------------
  0   | -2  |      0      |      -2     |      -2
  1   |  1  |     -2      |      -1     |      -1
  2   | -3  |     -1      |      -4     |      -1
       (reset cur = 0 because -4 < 0)
  3   |  4  |      0      |      4      |      4
  4   | -1  |      4      |      3      |      4
  5   |  2  |      3      |      5      |      5
  6   |  1  |      5      |      6      |      6
  7   | -5  |      6      |      1      |      6
  8   |  4  |      1      |      5      |      6
```

**Why This Works:**
- The algorithm exploits the fact that if a prefix sum is negative, it's always better to exclude it and start fresh
- By keeping only non-negative prefixes, we ensure we're always considering the best possible continuation
- Time: O(n), Space: O(1)

**Alternative: Divide and Conquer Approach**

```python
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        def maxSubArrayHelper(nums, left, right):
            if left == right:
                return nums[left]
            
            mid = (left + right) // 2
            
            # Recursively find max in left and right halves
            left_max = maxSubArrayHelper(nums, left, mid)
            right_max = maxSubArrayHelper(nums, mid + 1, right)
            
            # Find max crossing the middle
            left_sum = float('-inf')
            curr_sum = 0
            for i in range(mid, left - 1, -1):
                curr_sum += nums[i]
                left_sum = max(left_sum, curr_sum)
            
            right_sum = float('-inf')
            curr_sum = 0
            for i in range(mid + 1, right + 1):
                curr_sum += nums[i]
                right_sum = max(right_sum, curr_sum)
            
            return max(left_max, right_max, left_sum + right_sum)
        
        return maxSubArrayHelper(nums, 0, len(nums) - 1)
```

- Time: O(n log n), Space: O(log n) for recursion stack
- More complex but demonstrates divide-and-conquer paradigm

# Tags

- Array
- Dynamic Programming
- Greedy
- Divide and Conquer