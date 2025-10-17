## Problem

https://leetcode.com/problems/largest-number/description/

```
Given a list of non-negative integers nums, arrange them such that they form the largest number and return it.

Since the result may be very large, so you need to return a string instead of an integer.

Example 1:

Input: nums = [10,2]
Output: "210"

Example 2:

Input: nums = [3,30,34,5,9]
Output: "9534330"

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 109
```

## Observations

1. **Core Insight**: To form the largest number, we need to arrange numbers such that when concatenated, they produce the maximum possible value. This isn't simply sorting by numerical value.

2. **Custom Comparison**: For any two numbers `a` and `b`, we should place `a` before `b` if concatenating `a+b` results in a larger number than `b+a`. For example:
   - `3` vs `30`: `"3" + "30" = "330"` vs `"30" + "3" = "303"` → `330 > 303`, so `3` should come before `30`
   - `9` vs `5`: `"9" + "5" = "95"` vs `"5" + "9" = "59"` → `95 > 59`, so `9` should come before `5`

3. **Edge Cases**:
   - All zeros: `[0, 0, 0]` should return `"0"`, not `"000"`
   - Single element: `[0]` should return `"0"`
   - Mixed with zeros: `[0, 1, 2]` should handle leading zeros properly

4. **String Comparison**: Python's string comparison works lexicographically, which is perfect for comparing concatenated results.

## Solution

The solution uses a custom comparator with Python's `cmp_to_key` function to sort the numbers optimally.

**Algorithm Steps**:
1. **Custom Comparator**: Create a comparison function that determines the relative order of two numbers based on their concatenated results
2. **Sort**: Use the custom comparator to sort the array
3. **Handle Edge Case**: If the result is all zeros, return "0"

**Time Complexity**: O(n log n × m) where n is the number of elements and m is the average number of digits
**Space Complexity**: O(n × m) for string operations

## Tags

array, string, greedy