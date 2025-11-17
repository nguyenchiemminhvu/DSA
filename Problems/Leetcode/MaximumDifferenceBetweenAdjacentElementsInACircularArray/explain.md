## Problem

https://leetcode.com/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/description/

```
Given a circular array nums, find the maximum absolute difference between adjacent elements.

Note: In a circular array, the first and last elements are adjacent.

Example 1:

Input: nums = [1,2,4]

Output: 3

Explanation:

Because nums is circular, nums[0] and nums[2] are adjacent. They have the maximum absolute difference of |4 - 1| = 3.

Example 2:

Input: nums = [-5,-10,-5]

Output: 5

Explanation:

The adjacent elements nums[0] and nums[1] have the maximum absolute difference of |-5 - (-10)| = 5.

Constraints:

2 <= nums.length <= 100
-100 <= nums[i] <= 100
```

## Observations

1. **Circular Array Property**: The key insight is that in a circular array, the last element is adjacent to the first element. This means we need to consider the difference between `nums[n-1]` and `nums[0]` as well.

2. **Adjacent Elements**: We need to check all consecutive pairs:
   - `nums[0]` and `nums[1]`
   - `nums[1]` and `nums[2]`
   - ...
   - `nums[n-2]` and `nums[n-1]`
   - `nums[n-1]` and `nums[0]` (circular connection)

3. **Maximum Absolute Difference**: We need to find the maximum value among all absolute differences of adjacent pairs.

4. **Simple Approach**: Instead of handling the circular case separately, we can append the first element to the end of the array, making it linear and easier to process.

## Solution

1. **Handle Circular Property**: `nums.append(nums[0])` - We append the first element to the end of the array. This creates a linear representation where the last comparison will be between the original last element and the first element.

2. **Iterate Through Adjacent Pairs**: Starting from index 1, we compare each element with its previous element (`nums[i]` with `nums[i-1]`).

3. **Track Maximum Difference**: For each pair, we calculate the absolute difference and update our result if it's larger than the current maximum.

4. **Return Result**: After checking all adjacent pairs (including the circular connection), we return the maximum difference found.

**Example walkthrough:**
- Input: `nums = [1, 2, 4]`
- After appending: `nums = [1, 2, 4, 1]`
- Comparisons:
  - `|2 - 1| = 1`
  - `|4 - 2| = 2`
  - `|1 - 4| = 3` (circular connection)
- Maximum: 3

**Time Complexity**: O(n) - Single pass through the array
**Space Complexity**: O(1) - Only using constant extra space (modifying input array)

# Tags

- Array
- Circular Array
- Math
- Simulation

