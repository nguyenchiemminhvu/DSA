## Problem

https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/description

You are given an integer array `nums`. The absolute sum of a subarray `[nums[l], nums[l+1], ..., nums[r-1], nums[r]]` is `abs(nums[l] + nums[l+1] + ... + nums[r-1] + nums[r])`.

Return the **maximum absolute sum** of any (possibly empty) subarray of `nums`.

**Note:** `abs(x)` is defined as:
- If `x` is a negative integer, then `abs(x) = -x`
- If `x` is a non-negative integer, then `abs(x) = x`

### Examples

**Example 1:**
- Input: `nums = [1,-3,2,3,-4]`
- Output: `5`
- Explanation: The subarray `[2,3]` has absolute sum = `abs(2+3)` = `abs(5)` = `5`

**Example 2:**
- Input: `nums = [2,-5,1,-4,3,-2]`
- Output: `8`
- Explanation: The subarray `[-5,1,-4]` has absolute sum = `abs(-5+1-4)` = `abs(-8)` = `8`

### Constraints

- `1 <= nums.length <= 10^5`
- `-10^4 <= nums[i] <= 10^4`

## Observations

1. **Absolute Value Property:** The maximum absolute sum could come from either:
   - The maximum positive subarray sum
   - The minimum (most negative) subarray sum
   
   We need to find the maximum of `abs(max_sum)` and `abs(min_sum)`.

2. **Kadane's Algorithm Applicability:** This is a variant of the maximum subarray problem. Kadane's algorithm finds the maximum contiguous subarray sum in O(n) time.

3. **Two Passes Needed:** We need to run Kadane's algorithm twice:
   - Once to find the maximum subarray sum
   - Once to find the minimum subarray sum (by modifying the comparison operators)

4. **Greedy Choice:** At each position, we decide whether to:
   - Continue adding elements to the current subarray
   - Start a fresh subarray from the current element
   
   This choice is made greedily by comparing the current value with the sum of current value and all previous elements.

5. **Time Complexity:** O(n) - single pass through the array for each Kadane variant
   **Space Complexity:** O(1) - only using a few variables

## Solution

The key insight is to leverage **Kadane's algorithm** in two different ways:

### Approach: Modified Kadane's Algorithm

We run Kadane's algorithm twice:
1. **Find maximum subarray sum** using standard Kadane's algorithm
2. **Find minimum subarray sum** by using `min` instead of `max` at each step
3. Return the maximum of their absolute values

```python
class Solution:
    def maxAbsoluteSum(self, nums: List[int]) -> int:
        def kadane_max(arr: List[int]) -> int:
            """Find maximum subarray sum using Kadane's algorithm"""
            res = arr[0]
            cur_max = arr[0]
            for i in range(1, len(arr)):
                val = arr[i]
                # Either continue the sum or start fresh
                cur_max = max(val, cur_max + val)
                # Track the maximum seen so far
                res = max(res, cur_max)
            return res
        
        def kadane_min(arr: List[int]) -> int:
            """Find minimum subarray sum using modified Kadane's algorithm"""
            res = arr[0]
            cur_min = arr[0]
            for i in range(1, len(arr)):
                val = arr[i]
                # Either continue the sum or start fresh
                cur_min = min(val, cur_min + val)
                # Track the minimum seen so far
                res = min(res, cur_min)
            return res
        
        mx = kadane_max(nums)  # Maximum subarray sum
        mi = kadane_min(nums)  # Minimum subarray sum
        return max(abs(mi), abs(mx))  # Return maximum absolute value
```

### How It Works

Let's trace through Example 2: `nums = [2,-5,1,-4,3,-2]`

**Kadane's Max:**
- i=0: cur_max=2, res=2
- i=1: cur_max=max(-5, 2-5)=max(-5, -3)=-3, res=2
- i=2: cur_max=max(1, -3+1)=max(1, -2)=1, res=2
- i=3: cur_max=max(-4, 1-4)=max(-4, -3)=-3, res=2
- i=4: cur_max=max(3, -3+3)=max(3, 0)=3, res=3
- i=5: cur_max=max(-2, 3-2)=max(-2, 1)=1, res=3
- Result: mx = 3

**Kadane's Min:**
- i=0: cur_min=2, res=2
- i=1: cur_min=min(-5, 2-5)=min(-5, -3)=-5, res=-5
- i=2: cur_min=min(1, -5+1)=min(1, -4)=-4, res=-5
- i=3: cur_min=min(-4, -4-4)=min(-4, -8)=-8, res=-8
- i=4: cur_min=min(3, -8+3)=min(3, -5)=-5, res=-8
- i=5: cur_min=min(-2, -5-2)=min(-2, -7)=-7, res=-8
- Result: mi = -8

**Answer:** `max(abs(-8), abs(3))` = `max(8, 3)` = `8` ✓

### Complexity Analysis

- **Time Complexity:** O(n) - two passes through the array, each O(n)
- **Space Complexity:** O(1) - only using constant extra space

# Tags

#kadane_algorithm #dynamic_programming #subarray #maximum_absolute_sum

