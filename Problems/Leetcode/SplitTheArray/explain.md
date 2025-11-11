## Problem

https://leetcode.com/problems/split-the-array/description/

```
You are given an integer array nums of even length. You have to split the array into two parts nums1 and nums2 such that:

nums1.length == nums2.length == nums.length / 2.
nums1 should contain distinct elements.
nums2 should also contain distinct elements.
Return true if it is possible to split the array, and false otherwise.

Example 1:

Input: nums = [1,1,2,2,3,4]
Output: true
Explanation: One of the possible ways to split nums is nums1 = [1,2,3] and nums2 = [1,2,4].

Example 2:

Input: nums = [1,1,1,1]
Output: false
Explanation: The only possible way to split nums is nums1 = [1,1] and nums2 = [1,1]. Both nums1 and nums2 do not contain distinct elements. Therefore, we return false.

Constraints:

1 <= nums.length <= 100
nums.length % 2 == 0 
1 <= nums[i] <= 100
```

## Observations

1. **Key Constraint Analysis**: We need to split an even-length array into two equal parts where each part contains only distinct elements.

2. **Frequency Insight**: If any element appears more than 2 times in the original array, it's impossible to split because:
   - We have only 2 arrays to distribute elements to
   - Each array can contain at most 1 copy of any element (distinct requirement)
   - So any element can appear at most 2 times total

3. **Optimal Distribution**: For elements that appear exactly 2 times, we put one copy in each array. For elements that appear once, we can put them in either array.

4. **Length Guarantee**: Since the input array has even length and we're splitting into two equal parts, if no element appears more than twice, we can always achieve a valid split.

## Solution

**Algorithm**: Frequency Count + Validation

**Approach**:
1. Count the frequency of each element using `Counter`
2. Check if any element appears more than 2 times
3. If yes, return `False` (impossible to split)
4. If no element appears more than 2 times, return `True` (always possible)

**Key Insight**: The maximum frequency constraint (≤ 2) is the only condition we need to check. The even length and equal distribution are automatically satisfied due to the problem constraints.

**Time Complexity**: O(n) - single pass to count frequencies
**Space Complexity**: O(n) - for the Counter dictionary

**Example Walkthrough**:
- `[1,1,2,2,3,4]` → frequencies: {1:2, 2:2, 3:1, 4:1} → max freq = 2 ✓ → `True`
- `[1,1,1,1]` → frequencies: {1:4} → max freq = 4 > 2 ✗ → `False`

# Tags

Hash Table, Counting, Array, Greedy

