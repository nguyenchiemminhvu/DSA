## Problem

https://leetcode.com/problems/mean-of-array-after-removing-some-elements/description/

```
Given an integer array arr, return the mean of the remaining integers after removing the smallest 5% and the largest 5% of the elements.

Answers within 10-5 of the actual answer will be considered accepted.

Example 1:

Input: arr = [1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3]
Output: 2.00000
Explanation: After erasing the minimum and the maximum values of this array, all elements are equal to 2, so the mean is 2.

Example 2:

Input: arr = [6,2,7,5,1,2,0,3,10,2,5,0,5,5,0,8,7,6,8,0]
Output: 4.00000

Example 3:

Input: arr = [6,0,7,0,7,5,7,8,3,4,0,7,8,1,6,8,1,1,2,4,8,1,9,5,4,3,8,5,10,8,6,6,1,0,6,10,8,2,3,4]
Output: 4.77778

Constraints:

20 <= arr.length <= 1000
arr.length is a multiple of 20.
0 <= arr[i] <= 105
```

## Observations

1. **Problem Requirements**:
   - Remove the smallest 5% and largest 5% of elements from the array
   - Calculate the mean of the remaining elements
   - The array length is guaranteed to be a multiple of 20, ensuring 5% calculations result in whole numbers

2. **Key Insights**:
   - Since we need to remove 5% from both ends, sorting the array is the most straightforward approach
   - After sorting, we can simply slice the array to remove the first 5% and last 5% elements
   - The constraint that array length is a multiple of 20 ensures that 5% of the length is always an integer

3. **Mathematical Analysis**:
   - For an array of length n, we remove `5% × n = 0.05 × n` elements from each end
   - Since n is a multiple of 20, `5n/100 = n/20` is always an integer
   - Remaining elements: `n - 2 × (n/20) = n - n/10 = 9n/10`

4. **Edge Cases Handled**:
   - The constraint guarantees minimum length of 20, so we always have elements to remove and keep
   - No need to worry about empty arrays after removal due to the constraint

## Solution

1. **Sort the Array**: `arr.sort()`
   - Time complexity: O(n log n)
   - This arranges elements in ascending order, making it easy to identify the smallest and largest 5%

2. **Calculate Removal Indices**:
   - Start index: `int(5 * n // 100)` = number of elements to remove from the beginning
   - End index: `int(n - (5 * n // 100))` = position where we stop (excluding the last 5%)
   - Since n is a multiple of 20, `5 * n // 100` equals `n // 20`

3. **Extract Middle Elements**: `new_arr = arr[start:end]`
   - Slices the array to keep only the middle 90% of elements
   - Automatically removes the smallest 5% (first elements) and largest 5% (last elements)

4. **Calculate Mean**: `sum(new_arr) / new_n`
   - Simple arithmetic mean of the remaining elements

**Time Complexity**: O(n log n) - dominated by the sorting step
**Space Complexity**: O(n) - for the new array slice (could be optimized to O(1) by calculating sum without creating new array)

**Alternative Optimization** (Space-efficient):
```python
def trimMean(self, arr: List[int]) -> float:
    n = len(arr)
    arr.sort()
    remove_count = n // 20  # 5% of n
    total = sum(arr[remove_count:n-remove_count])
    return total / (n - 2 * remove_count)
```

# Tags

- **Array Processing**
- **Sorting** 
- **Mathematical Calculation**
- **Percentile Removal**
- **Statistics**

