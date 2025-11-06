## Problem

https://leetcode.com/problems/find-missing-elements/description/

```
You are given an integer array nums consisting of unique integers.

Originally, nums contained every integer within a certain range. However, some integers might have gone missing from the array.

The smallest and largest integers of the original range are still present in nums.

Return a sorted list of all the missing integers in this range. If no integers are missing, return an empty list.

Example 1:

Input: nums = [1,4,2,5]

Output: [3]

Explanation:

The smallest integer is 1 and the largest is 5, so the full range should be [1,2,3,4,5]. Among these, only 3 is missing.

Example 2:

Input: nums = [7,8,6,9]

Output: []

Explanation:

The smallest integer is 6 and the largest is 9, so the full range is [6,7,8,9]. All integers are already present, so no integer is missing.

Example 3:

Input: nums = [5,1]

Output: [2,3,4]

Explanation:

The smallest integer is 1 and the largest is 5, so the full range should be [1,2,3,4,5]. The missing integers are 2, 3, and 4.

Constraints:

2 <= nums.length <= 100
1 <= nums[i] <= 100
```

## Observations

1. **Problem Understanding**: We need to find all missing integers between the minimum and maximum values in the given array.

2. **Key Insights**:
   - The original range is defined by `[min(nums), max(nums)]`
   - We need to check which integers in this range are missing from the input array
   - The result should be sorted (naturally sorted since we iterate from left to right)

3. **Edge Cases**:
   - If all integers in the range are present, return empty list
   - The array contains unique integers, so no duplicates to handle
   - Minimum array length is 2, so we'll always have a valid range

4. **Approach Analysis**:
   - Using a set for O(1) lookup time is efficient
   - Time complexity: O(n + k) where n is array length and k is the range size
   - Space complexity: O(n) for the set

## Solution

1. **Find Range Boundaries**: Determine the minimum and maximum values to establish the original range
2. **Create Set**: Convert input array to set for efficient membership testing
3. **Iterate Through Range**: Check each value from `min` to `max-1` (exclusive upper bound)
4. **Collect Missing Elements**: Add any value not found in the set to result list

**Time Complexity**: O(n + k)
- O(n) to find min/max and create set
- O(k) to iterate through range, where k = max - min

**Space Complexity**: O(n) for the set storage

**Why This Works**:
- The set provides O(1) average case lookup time
- We only check the range between min and max (not the entire 1-100 range)
- The iteration naturally produces a sorted result

# Tags

Array, Hash Table, Set, Range Processing

