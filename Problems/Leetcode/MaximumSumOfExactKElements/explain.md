## Problem

https://leetcode.com/problems/maximum-sum-with-exactly-k-elements/description/

```
You are given a 0-indexed integer array nums and an integer k. Your task is to perform the following operation exactly k times in order to maximize your score:

Select an element m from nums.
Remove the selected element m from the array.
Add a new element with a value of m + 1 to the array.
Increase your score by m.
Return the maximum score you can achieve after performing the operation exactly k times.

Example 1:

Input: nums = [1,2,3,4,5], k = 3
Output: 18
Explanation: We need to choose exactly 3 elements from nums to maximize the sum.
For the first iteration, we choose 5. Then sum is 5 and nums = [1,2,3,4,6]
For the second iteration, we choose 6. Then sum is 5 + 6 and nums = [1,2,3,4,7]
For the third iteration, we choose 7. Then sum is 5 + 6 + 7 = 18 and nums = [1,2,3,4,8]
So, we will return 18.
It can be proven, that 18 is the maximum answer that we can achieve.

Example 2:

Input: nums = [5,5,5], k = 2
Output: 11
Explanation: We need to choose exactly 2 elements from nums to maximize the sum.
For the first iteration, we choose 5. Then sum is 5 and nums = [5,5,6]
For the second iteration, we choose 6. Then sum is 5 + 6 = 11 and nums = [5,5,7]
So, we will return 11.
It can be proven, that 11 is the maximum answer that we can achieve.

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100
1 <= k <= 100
```

## Observations

1. **Greedy Strategy**: To maximize the sum, we should always select the largest available element in the array at each step.

2. **Pattern Recognition**: 
   - Start with the maximum element `max_val` from the array
   - After k operations, we'll have selected: `max_val`, `max_val + 1`, `max_val + 2`, ..., `max_val + k - 1`
   - This forms an arithmetic sequence with first term `a = max_val` and last term `b = max_val + k - 1`

3. **Mathematical Insight**: The sum of an arithmetic sequence from `a` to `b` is:
   ```
   Sum = (number_of_terms) × (first_term + last_term) / 2
   Sum = (b - a + 1) × (a + b) / 2
   ```

4. **Optimization**: Instead of simulating k operations, we can directly calculate the result using the arithmetic sequence formula.

## Solution

The solution uses a mathematical approach to avoid simulation:

```python
class Solution:
    def maximizeSum(self, nums: List[int], k: int) -> int:
        a = max(nums)           # Starting value (maximum in array)
        b = a + k - 1          # Ending value after k operations
        return (b - a + 1) * (a + b) // 2  # Arithmetic sequence sum
```

**Step-by-step explanation:**

1. **Find the maximum**: `a = max(nums)` - This is the optimal starting point since we want to maximize our score.

2. **Calculate the final value**: `b = a + k - 1` - After k operations, the last value we'll select will be `a + k - 1`.

3. **Apply arithmetic sequence formula**: 
   - Number of terms: `b - a + 1 = k`
   - Sum formula: `k * (a + b) / 2`
   - Which simplifies to: `(b - a + 1) * (a + b) / 2`

**Example walkthrough** (nums = [1,2,3,4,5], k = 3):
- `a = max([1,2,3,4,5]) = 5`
- `b = 5 + 3 - 1 = 7` 
- Sum = `(7-5+1) * (5+7) / 2 = 3 * 12 / 2 = 18`
- This represents selecting: 5 + 6 + 7 = 18

**Time Complexity**: O(n) - only need to find the maximum element
**Space Complexity**: O(1) - constant extra space

## Tags

math, array, greedy