## Problem

https://leetcode.com/problems/maximum-average-subarray-i/description/

```
You are given an integer array nums consisting of n elements, and an integer k.

Find a contiguous subarray whose length is equal to k that has the maximum average value and return this value. Any answer with a calculation error less than 10-5 will be accepted.

Example 1:

Input: nums = [1,12,-5,-6,50,3], k = 4
Output: 12.75000
Explanation: Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75

Example 2:

Input: nums = [5], k = 1
Output: 5.00000

Constraints:

n == nums.length
1 <= k <= n <= 105
-104 <= nums[i] <= 104
```

## Observations

1. **Problem Type**: This is a classic sliding window problem where we need to find the maximum average of all possible subarrays of length `k`.

2. **Brute Force Approach**: A naive solution would calculate the sum of every subarray of length `k` and find the maximum average. This would have O(n*k) time complexity.

3. **Optimization Opportunity**: Since we're dealing with contiguous subarrays of fixed length, we can use the sliding window technique to achieve O(n) time complexity.

4. **Key Insight**: When moving from one subarray to the next:
   - We remove the leftmost element of the current window
   - We add the new rightmost element to the window
   - The sum changes by: `new_sum = old_sum - nums[i-k] + nums[i]`

5. **Mathematical Property**: Since all subarrays have the same length `k`, finding the maximum average is equivalent to finding the maximum sum (since `max(sum1/k, sum2/k) = max(sum1, sum2)/k`).

## Solution

**Step 1: Initialize the first window**
- Calculate the sum of the first `k` elements
- Set this as our initial result (`res = s / k`)

**Step 2: Slide the window**
- For each position from `k` to `n-1`:
  - Remove the element going out of the window: `s -= nums[i - k]`
  - Add the element coming into the window: `s += nums[i]`
  - Update the maximum average: `res = max(res, s / k)`

**Step 3: Return the result**
- Return the maximum average found

### Time and Space Complexity

- **Time Complexity**: O(n) where n is the length of the array
  - We iterate through the array twice: once to calculate the initial sum (O(k)) and once to slide the window (O(n-k))
  - Overall: O(k) + O(n-k) = O(n)

- **Space Complexity**: O(1)
  - We only use a constant amount of extra space for variables `s`, `res`, and loop counters

### Example Walkthrough

For `nums = [1,12,-5,-6,50,3]`, `k = 4`:

1. **Initial window [1,12,-5,-6]**: sum = 2, average = 0.5
2. **Window [12,-5,-6,50]**: sum = 51, average = 12.75 ✓ (maximum so far)
3. **Window [-5,-6,50,3]**: sum = 42, average = 10.5

Result: 12.75

# Tags

- **Sliding Window**
- **Array**
- **Two Pointers**

