## Problem

https://leetcode.com/problems/minimum-sum-of-mountain-triplets-i/

```
You are given a 0-indexed array nums of integers.

A triplet of indices (i, j, k) is a mountain if:

i < j < k
nums[i] < nums[j] and nums[k] < nums[j]
Return the minimum possible sum of a mountain triplet of nums. If no such triplet exists, return -1.

Example 1:

Input: nums = [8,6,1,5,3]
Output: 9
Explanation: Triplet (2, 3, 4) is a mountain triplet of sum 9 since: 
- 2 < 3 < 4
- nums[2] < nums[3] and nums[4] < nums[3]
And the sum of this triplet is nums[2] + nums[3] + nums[4] = 9. It can be shown that there are no mountain triplets with a sum of less than 9.

Example 2:

Input: nums = [5,4,8,7,10,2]
Output: 13
Explanation: Triplet (1, 3, 5) is a mountain triplet of sum 13 since: 
- 1 < 3 < 5
- nums[1] < nums[3] and nums[5] < nums[3]
And the sum of this triplet is nums[1] + nums[3] + nums[5] = 13. It can be shown that there are no mountain triplets with a sum of less than 13.

Example 3:

Input: nums = [6,5,4,3,4,5]
Output: -1
Explanation: It can be shown that there are no mountain triplets in nums.

Constraints:

3 <= nums.length <= 50
1 <= nums[i] <= 50
```

## Observations

**Key Insights:**
1. **Mountain Structure**: For a valid mountain triplet (i, j, k), element at index j must be the "peak" - larger than both its left element (at i) and right element (at k).

2. **Optimization Strategy**: Instead of checking all possible triplets (O(n³) approach), we can fix the middle element (peak) and find the smallest possible left and right elements that satisfy the mountain condition.

3. **Preprocessing Approach**: 
   - For each position, precompute the minimum element to its left
   - For each position, precompute the minimum element to its right
   - This allows O(1) lookup when checking each potential peak

4. **Constraint Analysis**: With n ≤ 50, even O(n³) would work, but the O(n) solution is more elegant and scalable.

## Solution

1. **Left Minimum Array (`min_left`)**:
   - `min_left[i]` stores the minimum value from index 0 to i
   - This gives us the smallest possible left element for any peak at position > i

2. **Right Minimum Array (`min_right`)**:
   - `min_right[i]` stores the minimum value from index i to n-1
   - This gives us the smallest possible right element for any peak at position < i

3. **Peak Validation**:
   - For each middle position i (1 to n-2), check if it can be a valid peak
   - Condition: `min_left[i-1] < nums[i] > min_right[i+1]`
   - If valid, calculate sum: `min_left[i-1] + nums[i] + min_right[i+1]`

**Example Walkthrough (nums = [8,6,1,5,3]):**

```
Original: [8, 6, 1, 5, 3]
Indices:  [0, 1, 2, 3, 4]

min_left:  [8, 6, 1, 1, 1]
min_right: [1, 1, 1, 3, 3]

Check i=1: min_left[0]=8, nums[1]=6, min_right[2]=1
          8 < 6? No → Invalid peak

Check i=2: min_left[1]=6, nums[2]=1, min_right[3]=3  
          6 < 1? No → Invalid peak

Check i=3: min_left[2]=1, nums[3]=5, min_right[4]=3
          1 < 5 > 3? Yes → Valid peak!
          Sum = 1 + 5 + 3 = 9
```

**Time Complexity:** O(n) - Single pass for each preprocessing step + one pass for checking peaks  
**Space Complexity:** O(n) - For the min_left and min_right arrays

**Alternative O(1) Space Approach:**
While the current solution uses O(n) space, we could optimize to O(1) space by computing minimums on-the-fly, but it would increase time complexity to O(n²).

# Tags

