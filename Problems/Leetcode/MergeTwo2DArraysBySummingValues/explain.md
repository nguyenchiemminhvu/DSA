## Problem

https://leetcode.com/problems/merge-two-2d-arrays-by-summing-values/

```
You are given two 2D integer arrays nums1 and nums2.

nums1[i] = [idi, vali] indicate that the number with the id idi has a value equal to vali.
nums2[i] = [idi, vali] indicate that the number with the id idi has a value equal to vali.
Each array contains unique ids and is sorted in ascending order by id.

Merge the two arrays into one array that is sorted in ascending order by id, respecting the following conditions:

Only ids that appear in at least one of the two arrays should be included in the resulting array.
Each id should be included only once and its value should be the sum of the values of this id in the two arrays. If the id does not exist in one of the two arrays, then assume its value in that array to be 0.
Return the resulting array. The returned array must be sorted in ascending order by id.

Example 1:

Input: nums1 = [[1,2],[2,3],[4,5]], nums2 = [[1,4],[3,2],[4,1]]
Output: [[1,6],[2,3],[3,2],[4,6]]
Explanation: The resulting array contains the following:
- id = 1, the value of this id is 2 + 4 = 6.
- id = 2, the value of this id is 3.
- id = 3, the value of this id is 2.
- id = 4, the value of this id is 5 + 1 = 6.

Example 2:

Input: nums1 = [[2,4],[3,6],[5,5]], nums2 = [[1,3],[4,3]]
Output: [[1,3],[2,4],[3,6],[4,3],[5,5]]
Explanation: There are no common ids, so we just include each id with its value in the resulting list.

Constraints:

1 <= nums1.length, nums2.length <= 200
nums1[i].length == nums2[j].length == 2
1 <= idi, vali <= 1000
Both arrays contain unique ids.
Both arrays are in strictly ascending order by id.
```

## Observations

1. **Input Structure**: Both arrays contain pairs `[id, value]` where each id is unique within its array and arrays are sorted by id.

2. **Merge Strategy**: We need to combine values for matching ids and include all unique ids from both arrays.

3. **Output Requirements**: Return array sorted by id in ascending order.

4. **Key Insights**:
   - Use a hash map/dictionary to aggregate values by id
   - If an id appears in both arrays, sum their values
   - If an id appears in only one array, use that value directly
   - Sort the final result by id

## Solution

1. **Initialize Dictionary**: Create an empty dictionary `f` to store id-value mappings.

2. **Process First Array**: 
   - Iterate through array `a`
   - For each `[k, v]` pair, add value `v` to the existing value for key `k` (or 0 if key doesn't exist)
   - `f.get(k, 0)` returns current value for key `k` or 0 if key doesn't exist

3. **Process Second Array**:
   - Similarly iterate through array `b`
   - Add values to existing keys or create new entries

4. **Generate Result**:
   - Convert dictionary items back to list of `[id, value]` pairs
   - Sort by id (key=lambda x: x[0]) to ensure ascending order

**Time Complexity**: O(n + m + k log k) where n, m are lengths of input arrays and k is number of unique ids
**Space Complexity**: O(k) for the dictionary storing unique ids

**Example Walkthrough**:
- `nums1 = [[1,2],[2,3],[4,5]]`, `nums2 = [[1,4],[3,2],[4,1]]`
- After processing `nums1`: `f = {1: 2, 2: 3, 4: 5}`
- After processing `nums2`: `f = {1: 6, 2: 3, 3: 2, 4: 6}`
- Final sorted result: `[[1,6],[2,3],[3,2],[4,6]]`

# Tags

Hash Table, Array, Sorting

