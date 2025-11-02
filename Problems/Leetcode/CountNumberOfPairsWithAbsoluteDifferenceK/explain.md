## Problem

https://leetcode.com/problems/count-number-of-pairs-with-absolute-difference-k/

```
Given an integer array nums and an integer k, return the number of pairs (i, j) where i < j such that |nums[i] - nums[j]| == k.

The value of |x| is defined as:

x if x >= 0.
-x if x < 0.

Example 1:

Input: nums = [1,2,2,1], k = 1
Output: 4
Explanation: The pairs with an absolute difference of 1 are:
- [1,2,2,1]
- [1,2,2,1]
- [1,2,2,1]
- [1,2,2,1]

Example 2:

Input: nums = [1,3], k = 3
Output: 0
Explanation: There are no pairs with an absolute difference of 3.

Example 3:

Input: nums = [3,2,1,5,4], k = 2
Output: 3
Explanation: The pairs with an absolute difference of 2 are:
- [3,2,1,5,4]
- [3,2,1,5,4]
- [3,2,1,5,4]

Constraints:

1 <= nums.length <= 200
1 <= nums[i] <= 100
1 <= k <= 99
```

## Observations

1. **Understanding the problem**: We need to count pairs (i, j) where i < j and |nums[i] - nums[j]| == k
   - The absolute difference means either nums[i] - nums[j] = k or nums[j] - nums[i] = k
   - This translates to: nums[i] = nums[j] + k OR nums[j] = nums[i] + k

2. **Key insight**: For any value `x` in the array, we can form pairs with:
   - Values equal to `x + k` (where x is the smaller value)
   - Values equal to `x - k` (where x is the larger value)
   - But since we're looking for |difference| = k, we only need to count one direction to avoid double counting

3. **Frequency counting approach**: 
   - Count frequency of each number in the array
   - For each unique value, count how many pairs it can form with value + k
   - This automatically handles the constraint i < j without explicit index tracking

4. **Why sorting helps**: While not strictly necessary for correctness, sorting ensures we process smaller values first, making the logic cleaner (we only look for val + k, not val - k)

## Solution

1. **Frequency Map Creation**: 
   - Create a dictionary to store the frequency of each number
   - Sorting is optional but makes the logic clearer

2. **Pair Counting Logic**:
   - For each unique value `val` with frequency `f1`
   - Look for value `val + k` with frequency `f2`
   - The number of pairs between these two values is `f1 * f2`
   - This is because each occurrence of `val` can pair with each occurrence of `val + k`

3. **Why this works**:
   - We only count pairs where the first element is smaller (val < val + k)
   - This automatically satisfies the i < j constraint when considering the original array positions
   - We avoid double counting by only looking in one direction (val + k, not val - k)

**Example Walkthrough** (nums = [1,2,2,1], k = 1):
- Frequency map: {1: 2, 2: 2}
- For val = 1: freq[1] * freq[1+1] = 2 * 2 = 4 pairs
- For val = 2: freq[2] * freq[2+1] = 2 * 0 = 0 pairs
- Total: 4 pairs

**Time Complexity**: O(n log n) due to sorting, or O(n) if we skip sorting
**Space Complexity**: O(n) for the frequency map

## Tags

- Hash Map
- Frequency Counting
- Array
- Two Pointers (conceptual)