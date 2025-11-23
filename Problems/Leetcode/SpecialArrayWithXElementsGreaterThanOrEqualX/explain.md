## Problem

https://leetcode.com/problems/special-array-with-x-elements-greater-than-or-equal-x/description/

```
You are given an array nums of non-negative integers. nums is considered special if there exists a number x such that there are exactly x numbers in nums that are greater than or equal to x.

Notice that x does not have to be an element in nums.

Return x if the array is special, otherwise, return -1. It can be proven that if nums is special, the value for x is unique.

Example 1:

Input: nums = [3,5]
Output: 2
Explanation: There are 2 values (3 and 5) that are greater than or equal to 2.

Example 2:

Input: nums = [0,0]
Output: -1
Explanation: No numbers fit the criteria for x.
If x = 0, there should be 0 numbers >= x, but there are 2.
If x = 1, there should be 1 number >= x, but there are 0.
If x = 2, there should be 2 numbers >= x, but there are 0.
x cannot be greater since there are only 2 numbers in nums.

Example 3:

Input: nums = [0,4,3,0,4]
Output: 3
Explanation: There are 3 values that are greater than or equal to 3.

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 1000
```

## Observations

1. **Problem Analysis**: We need to find a value `x` such that exactly `x` numbers in the array are greater than or equal to `x`.

2. **Key Insights**:
   - The value `x` can range from 0 to `len(nums)` (inclusive)
   - If more than `len(nums)` elements were >= x, then x would need to be > len(nums), but we only have len(nums) elements
   - We need to count how many elements are >= x for each possible value of x

3. **Approach**: 
   - Try each possible value of x from 0 to len(nums)
   - For each x, count how many numbers in nums are >= x
   - If the count equals x, we found our answer

4. **Optimization**: Instead of checking each element for every x, we can:
   - Use a frequency counter to group identical values
   - Sort the unique values
   - Use binary search (lower_bound) to find the first value >= x
   - Sum frequencies of all values from that position onwards

## Solution

1. **Frequency Counter**: Create a counter `f` to store frequency of each unique value in nums
2. **Sorted Keys**: Get sorted unique values from the counter
3. **Binary Search Helper**: `lower_bound` function finds the first index in sorted array where value >= target
4. **Main Logic**: 
   - For each possible x (0 to len(nums)):
     - Find first position where keys[i] >= x using binary search
     - Sum frequencies of all keys from that position onwards
     - If sum equals x, return x
5. **Return -1**: If no valid x found

**Time Complexity**: O(n log k + k*n) where k is number of unique elements
- O(n) for Counter creation
- O(k log k) for sorting unique keys  
- O(n * log k) for n binary searches
- O(n * k) for counting frequencies

**Space Complexity**: O(k) for storing unique values and their frequencies

**Example Walkthrough** with nums = [3,5]:
- f = {3: 1, 5: 1}, keys = [3, 5]
- x = 0: lower_bound([3,5], 0) = 0, count = 1+1 = 2 ≠ 0
- x = 1: lower_bound([3,5], 1) = 0, count = 1+1 = 2 ≠ 1  
- x = 2: lower_bound([3,5], 2) = 0, count = 1+1 = 2 = 2 ✓
- Return 2

# Tags

