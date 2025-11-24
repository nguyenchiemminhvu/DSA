## Problem

https://leetcode.com/problems/maximum-ascending-subarray-sum/description/

```
Given an array of positive integers nums, return the maximum possible sum of an strictly increasing subarray in nums.

A subarray is defined as a contiguous sequence of numbers in an array.

Example 1:

Input: nums = [10,20,30,5,10,50]
Output: 65
Explanation: [5,10,50] is the ascending subarray with the maximum sum of 65.

Example 2:

Input: nums = [10,20,30,40,50]
Output: 150
Explanation: [10,20,30,40,50] is the ascending subarray with the maximum sum of 150.

Example 3:

Input: nums = [12,17,15,13,10,11,12]
Output: 33
Explanation: [10,11,12] is the ascending subarray with the maximum sum of 33.

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100
```

## Observations

1. **Problem Nature**: We need to find the maximum sum of a strictly increasing contiguous subarray.

2. **Key Insight**: A strictly increasing subarray breaks when we encounter a number that is not greater than the previous one.

3. **Approach**: We can use a modified prefix sum approach where we accumulate sums only when the sequence is strictly increasing, and reset when it's not.

4. **Edge Cases**: 
   - Single element arrays (minimum constraint is 1 element)
   - Arrays where no two consecutive elements form an increasing sequence
   - Entire array is strictly increasing

## Solution

1. **Initialize**: Create a prefix array as a copy of the original array. Each position initially contains just the value at that index.

2. **Build Cumulative Sums**: 
   - Iterate through the array starting from index 1
   - If `nums[i] > nums[i-1]` (strictly increasing), add the previous cumulative sum to current position
   - If not strictly increasing, the cumulative sum "resets" and only contains the current element

3. **Find Maximum**: Return the maximum value in the prefix array, which represents the maximum sum of any ascending subarray.

**Example Walkthrough** (`nums = [10,20,30,5,10,50]`):

- Initial: `prefix = [10, 20, 30, 5, 10, 50]`
- i=1: `20 > 10` → `prefix[1] = 20 + 10 = 30` → `[10, 30, 30, 5, 10, 50]`
- i=2: `30 > 20` → `prefix[2] = 30 + 30 = 60` → `[10, 30, 60, 5, 10, 50]`
- i=3: `5 < 30` → no change → `[10, 30, 60, 5, 10, 50]`
- i=4: `10 > 5` → `prefix[4] = 10 + 5 = 15` → `[10, 30, 60, 5, 15, 50]`
- i=5: `50 > 10` → `prefix[5] = 50 + 15 = 65` → `[10, 30, 60, 5, 15, 65]`
- Result: `max([10, 30, 60, 5, 15, 65]) = 65`

**Time Complexity**: O(n) - single pass through the array
**Space Complexity**: O(n) - for the prefix array

**Alternative O(1) Space Solution**:
```python
def maxAscendingSum(self, nums: List[int]) -> int:
    max_sum = current_sum = nums[0]
    
    for i in range(1, len(nums)):
        if nums[i] > nums[i-1]:
            current_sum += nums[i]
        else:
            current_sum = nums[i]
        max_sum = max(max_sum, current_sum)
    
    return max_sum
```

# Tags
`Array`, `Prefix Sum`, `Dynamic Programming`, `Greedy`

