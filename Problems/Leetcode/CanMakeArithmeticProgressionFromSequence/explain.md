## Problem

https://leetcode.com/problems/can-make-arithmetic-progression-from-sequence/description/

```
A sequence of numbers is called an arithmetic progression if the difference between any two consecutive elements is the same.

Given an array of numbers arr, return true if the array can be rearranged to form an arithmetic progression. Otherwise, return false.

Example 1:

Input: arr = [3,5,1]
Output: true
Explanation: We can reorder the elements as [1,3,5] or [5,3,1] with differences 2 and -2 respectively, between each consecutive elements.

Example 2:

Input: arr = [1,2,4]
Output: false
Explanation: There is no way to reorder the elements to obtain an arithmetic progression.

Constraints:

2 <= arr.length <= 1000
-106 <= arr[i] <= 106
```

## Observations

1. **Arithmetic Progression Definition**: In an arithmetic progression, the difference between any two consecutive elements must be constant.

2. **Key Insight**: If we can rearrange the array to form an arithmetic progression, then sorting the array will give us the correct order (either ascending or descending).

3. **Algorithm Approach**: 
   - Sort the array first
   - Calculate the common difference using the first two elements
   - Check if all consecutive pairs have the same difference

4. **Edge Cases**: 
   - Arrays with length 2 will always form an arithmetic progression
   - All elements being the same (difference = 0) is valid

## Solution

1. **Sort the Array**: `arr.sort()`
   - Sorting ensures that if an arithmetic progression is possible, the elements will be in the correct order
   - Time complexity: O(n log n)

2. **Calculate Initial Difference**: `diff = arr[1] - arr[0]`
   - Use the first two elements to determine what the common difference should be
   - This works because after sorting, if AP is possible, these will be consecutive terms

3. **Validate All Consecutive Differences**: 
   ```python
   for i in range(2, n):
       if arr[i] - arr[i - 1] != diff:
           return False
   ```
   - Check each consecutive pair starting from index 2
   - If any pair has a different difference, return False immediately

4. **Return True**: If all differences match, the array can form an arithmetic progression

**Time Complexity**: O(n log n) - dominated by sorting
**Space Complexity**: O(1) - only using constant extra space (sorting in-place)

**Example Walkthrough:**
- Input: `[3,5,1]`
- After sorting: `[1,3,5]`
- diff = 3 - 1 = 2
- Check: 5 - 3 = 2 ✓ (matches diff)
- Result: True

**Why This Works:**
If an array can be rearranged to form an arithmetic progression, then when sorted, it will naturally be in arithmetic progression order (either increasing or decreasing). The sorting step eliminates the need to consider all possible arrangements.

# Tags

array