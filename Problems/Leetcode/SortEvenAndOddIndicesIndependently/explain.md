## Problem

https://leetcode.com/problems/sort-even-and-odd-indices-independently/description/

```
You are given a 0-indexed integer array nums. Rearrange the values of nums according to the following rules:

1. Sort the values at odd indices of nums in non-increasing order.
   - For example, if nums = [4,1,2,3] before this step, it becomes [4,3,2,1] after. 
     The values at odd indices 1 and 3 are sorted in non-increasing order.

2. Sort the values at even indices of nums in non-decreasing order.
   - For example, if nums = [4,1,2,3] before this step, it becomes [2,1,4,3] after. 
     The values at even indices 0 and 2 are sorted in non-decreasing order.

Return the array formed after rearranging the values of nums.

Example 1:
Input: nums = [4,1,2,3]
Output: [2,3,4,1]
Explanation: 
First, we sort the values present at odd indices (1 and 3) in non-increasing order.
So, nums changes from [4,1,2,3] to [4,3,2,1].
Next, we sort the values present at even indices (0 and 2) in non-decreasing order.
So, nums changes from [4,1,2,3] to [2,3,4,1].
Thus, the array formed after rearranging the values is [2,3,4,1].

Example 2:
Input: nums = [2,1]
Output: [2,1]
Explanation: 
Since there is exactly one odd index and one even index, no rearrangement of values takes place.
The resultant array formed is [2,1], which is the same as the initial array.

Constraints:
- 1 <= nums.length <= 100
- 1 <= nums[i] <= 100
```

## Observations

1. **Index-based sorting**: We need to sort values at different indices differently:
   - Even indices (0, 2, 4, ...) → sort in ascending order
   - Odd indices (1, 3, 5, ...) → sort in descending order

2. **Independent sorting**: The values at even and odd indices are sorted independently of each other, then placed back at their respective positions.

3. **Small constraints**: With n ≤ 100, we don't need to worry about optimization - a simple O(n log n) solution works perfectly.

4. **Two-phase approach**: We can solve this in two separate phases:
   - Phase 1: Extract, sort, and replace even-indexed values
   - Phase 2: Extract, sort (descending), and replace odd-indexed values

## Solution

1. **Extract even-indexed values**: Use list comprehension `[nums[i] for i in range(0, n, 2)]` to collect all values at even positions (0, 2, 4, ...).

2. **Sort ascending**: Sort the extracted values in ascending order using `sort()`.

3. **Place back**: Iterate through even indices again and place the sorted values back into their positions.

4. **Repeat for odd indices**: Do the same process for odd-indexed values (1, 3, 5, ...), but sort in descending order using `sort(reverse=True)`.

5. **Return result**: The modified array now has even indices sorted ascending and odd indices sorted descending.

**Complexity Analysis:**
- Time Complexity: O(n log n) - dominated by the two sorting operations
- Space Complexity: O(n) - for the temporary arrays storing even/odd indexed values

**Example Walkthrough** (nums = [4,1,2,3]):
- Initial: [4,1,2,3]
- Extract even indices: [4,2] → sort → [2,4]
- After placing back: [2,1,4,3]
- Extract odd indices: [1,3] → sort descending → [3,1]
- Final result: [2,3,4,1]

# Tags
#array #sorting #two-pointers #simulation

