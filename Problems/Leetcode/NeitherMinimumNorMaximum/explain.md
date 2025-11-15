## Problem

https://leetcode.com/problems/neither-minimum-nor-maximum/description/

```
Given an integer array nums containing distinct positive integers, find and return any number from the array that is neither the minimum nor the maximum value in the array, or -1 if there is no such number.

Return the selected integer.

Example 1:

Input: nums = [3,2,1,4]
Output: 2
Explanation: In this example, the minimum value is 1 and the maximum value is 4. Therefore, either 2 or 3 can be valid answers.

Example 2:

Input: nums = [1,2]
Output: -1
Explanation: Since there is no number in nums that is neither the maximum nor the minimum, we cannot select a number that satisfies the given condition. Therefore, there is no answer.

Example 3:

Input: nums = [2,1,3]
Output: 2
Explanation: Since 2 is neither the maximum nor the minimum value in nums, it is the only valid answer. 

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100
All values in nums are distinct
```

## Observations

1. **Problem Requirements**: Find any number that is neither minimum nor maximum in the array
2. **Array Properties**: 
   - Contains distinct positive integers
   - Length between 1 and 100
   - Values between 1 and 100
3. **Edge Cases**:
   - If array has length ≤ 2, impossible to have a middle value → return -1
   - If array has length ≥ 3, there must exist at least one middle value
4. **Key Insight**: We only need to find ONE valid answer, not all possible answers
5. **Approach**: Linear scan through array, skip min/max values, return first valid number found

## Solution

1. **Find Boundaries**: Calculate minimum (`mi`) and maximum (`ma`) values in the array
   - Time: O(n) to traverse array twice
   
2. **Linear Search**: Iterate through the array once more
   - For each value, check if it equals min or max
   - If not, it's a valid middle value → return immediately
   
3. **Edge Case Handling**: If no middle value found, return -1
   - This happens when array length ≤ 2

**Time Complexity**: O(n)
- O(n) to find min/max + O(n) worst case to find middle value = O(n)

**Space Complexity**: O(1)
- Only storing min, max, and loop variables

**Why This Works:**
- Since all values are distinct, any value that isn't min or max is automatically a valid answer
- We don't need to sort or find the exact middle - any non-extremum works
- Early return optimizes for best case when middle value appears early in array

**Alternative Approaches:**
- Sort array and return middle element: O(n log n) time
- Use selection algorithm: O(n) average time but more complex
- Current solution is optimal: O(n) time with simple implementation

# Tags

Array, Linear Search, Min/Max, Easy

