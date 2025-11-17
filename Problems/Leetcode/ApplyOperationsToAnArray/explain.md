## Problem

https://leetcode.com/problems/apply-operations-to-an-array/description/

```
You are given a 0-indexed array nums of size n consisting of non-negative integers.

You need to apply n - 1 operations to this array where, in the ith operation (0-indexed), you will apply the following on the ith element of nums:

If nums[i] == nums[i + 1], then multiply nums[i] by 2 and set nums[i + 1] to 0. Otherwise, you skip this operation.
After performing all the operations, shift all the 0's to the end of the array.

For example, the array [1,0,2,0,0,1] after shifting all its 0's to the end, is [1,2,1,0,0,0].
Return the resulting array.

Note that the operations are applied sequentially, not all at once.

Example 1:

Input: nums = [1,2,2,1,1,0]
Output: [1,4,2,0,0,0]
Explanation: We do the following operations:
- i = 0: nums[0] and nums[1] are not equal, so we skip this operation.
- i = 1: nums[1] and nums[2] are equal, we multiply nums[1] by 2 and change nums[2] to 0. The array becomes [1,4,0,1,1,0].
- i = 2: nums[2] and nums[3] are not equal, so we skip this operation.
- i = 3: nums[3] and nums[4] are equal, we multiply nums[3] by 2 and change nums[4] to 0. The array becomes [1,4,0,2,0,0].
- i = 4: nums[4] and nums[5] are equal, we multiply nums[4] by 2 and change nums[5] to 0. The array becomes [1,4,0,2,0,0].
After that, we shift the 0's to the end, which gives the array [1,4,2,0,0,0].

Example 2:

Input: nums = [0,1]
Output: [1,0]
Explanation: No operation can be applied, we just shift the 0 to the end.

Constraints:

2 <= nums.length <= 2000
0 <= nums[i] <= 1000
```

## Observations

1. **Two-Phase Process**: The problem requires two distinct phases:
   - Phase 1: Apply multiplication operations when adjacent elements are equal
   - Phase 2: Move all zeros to the end of the array

2. **Sequential Operations**: Operations must be applied sequentially from left to right, not simultaneously. This means when we process `nums[i]` and `nums[i+1]`, we use the current state of the array (which might have been modified by previous operations).

3. **Operation Rules**: 
   - If `nums[i] == nums[i+1]`, multiply `nums[i]` by 2 and set `nums[i+1]` to 0
   - Otherwise, skip the operation
   - We perform `n-1` operations (for indices 0 to n-2)

4. **Zero Shifting**: After all multiplication operations, we need to move all zeros to the end while maintaining the relative order of non-zero elements.

5. **Edge Cases to Consider**:
   - Arrays with consecutive equal elements
   - Arrays that are already processed (no equal adjacent elements)
   - Arrays with existing zeros
   - Single element arrays (though constraints say n >= 2)

## Solution

**Phase 1 - Apply Operations (Lines 5-8):**
- Iterate from index 1 to n-1 (processing pairs (i-1, i))
- For each position, check if `nums[i-1] == nums[i]`
- If equal: multiply `nums[i-1]` by 2 and set `nums[i]` to 0
- This processes operations sequentially as required

**Phase 2 - Move Zeros to End (Lines 10-22):**
- Use a two-pointer approach:
  - `i`: write pointer for placing non-zero elements
  - `c0`: counter for zeros encountered
- First pass: iterate through array, place non-zeros at the beginning and count zeros
- Second pass: fill remaining positions with zeros

### Time and Space Complexity:

- **Time Complexity**: O(n) where n is the length of the array
  - Phase 1: O(n) for the multiplication operations
  - Phase 2: O(n) for moving zeros to end
  - Total: O(n)

- **Space Complexity**: O(1) - only using a few extra variables (c0, i)

### Example Walkthrough:

For `nums = [1,2,2,1,1,0]`:

**Phase 1:**
- i=1: nums[0]=1, nums[1]=2 → not equal, skip
- i=2: nums[1]=2, nums[2]=2 → equal, nums[1]=4, nums[2]=0 → [1,4,0,1,1,0]
- i=3: nums[2]=0, nums[3]=1 → not equal, skip
- i=4: nums[3]=1, nums[4]=1 → equal, nums[3]=2, nums[4]=0 → [1,4,0,2,0,0]
- i=5: nums[4]=0, nums[5]=0 → equal, nums[4]=0, nums[5]=0 → [1,4,0,2,0,0]

**Phase 2:**
- Process [1,4,0,2,0,0]: non-zeros are [1,4,2], zeros count = 3
- Result: [1,4,2,0,0,0]

# Tags

`Array` `Two Pointers` `Simulation`

