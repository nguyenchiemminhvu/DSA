## Problem

https://leetcode.com/problems/rank-transform-of-an-array/description/

```
Given an array of integers arr, replace each element with its rank.

The rank represents how large the element is. The rank has the following rules:

Rank is an integer starting from 1.
The larger the element, the larger the rank. If two elements are equal, their rank must be the same.
Rank should be as small as possible.

Example 1:

Input: arr = [40,10,20,30]
Output: [4,1,2,3]
Explanation: 40 is the largest element. 10 is the smallest. 20 is the second smallest. 30 is the third smallest.

Example 2:

Input: arr = [100,100,100]
Output: [1,1,1]
Explanation: Same elements share the same rank.

Example 3:

Input: arr = [37,12,28,9,100,56,80,5,12]
Output: [5,3,4,2,8,6,7,1,3]

Constraints:

0 <= arr.length <= 105
-109 <= arr[i] <= 109
```

## Observations

1. **Problem Analysis**: We need to transform each element in the array to its rank based on its relative size compared to other elements.

2. **Key Rules**:
   - Rank starts from 1 (smallest element gets rank 1)
   - Larger elements get larger ranks
   - Equal elements get the same rank
   - Ranks should be consecutive (no gaps)

3. **Approach Strategy**: 
   - We need to find unique elements and sort them to determine their relative order
   - Create a mapping from each unique value to its rank
   - Apply this mapping to the original array

4. **Edge Cases**:
   - Empty array: Return empty array
   - All elements are the same: All get rank 1
   - Array with duplicates: Same values get same rank

## Solution

1. **`set(arr)`**: Remove duplicates from the array to get unique elements
2. **`sorted(set(arr))`**: Sort unique elements in ascending order
3. **Dictionary Comprehension**: Create a mapping where:
   - Key: unique element value
   - Value: rank (position + 1, since ranks start from 1)
4. **List Comprehension**: Transform original array by looking up each element's rank

**Example Walkthrough** (`arr = [40,10,20,30]`):
1. `set(arr)` → `{40, 10, 20, 30}`
2. `sorted(set(arr))` → `[10, 20, 30, 40]`
3. `fr` → `{10: 1, 20: 2, 30: 3, 40: 4}`
4. Result → `[fr[40], fr[10], fr[20], fr[30]]` → `[4, 1, 2, 3]`

**Time Complexity**: O(n log n) due to sorting
**Space Complexity**: O(n) for the dictionary and set

# Tags

- Array
- Sorting
- Hash Table/Dictionary
- Coordinate Compression

