## Problem

https://leetcode.com/problems/sum-of-good-numbers/description/

```
Given an array of integers nums and an integer k, an element nums[i] is considered good if it is strictly greater than the elements at indices i - k and i + k (if those indices exist). If neither of these indices exists, nums[i] is still considered good.

Return the sum of all the good elements in the array.

Example 1:

Input: nums = [1,3,2,1,5,4], k = 2

Output: 12

Explanation:

The good numbers are nums[1] = 3, nums[4] = 5, and nums[5] = 4 because they are strictly greater than the numbers at indices i - k and i + k.

Example 2:

Input: nums = [2,1], k = 1

Output: 2

Explanation:

The only good number is nums[0] = 2 because it is strictly greater than nums[1].

Constraints:

2 <= nums.length <= 100
1 <= nums[i] <= 1000
1 <= k <= floor(nums.length / 2)
```

## Observations

1. **Definition of "Good" Element**: An element `nums[i]` is considered "good" if it's strictly greater than:
   - The element at index `i - k` (if it exists)
   - The element at index `i + k` (if it exists)

2. **Edge Cases**: 
   - If `i - k < 0` (index doesn't exist), we don't need to check the left condition
   - If `i + k >= n` (index doesn't exist), we don't need to check the right condition
   - If both indices don't exist, the element is automatically good

3. **Key Insight**: We need to check both directions (left and right) from the current position at distance `k`. The element must be strictly greater than BOTH neighbors (if they exist).

4. **Example Analysis**:
   - For `nums = [1,3,2,1,5,4], k = 2`:
     - `nums[0] = 1`: No left neighbor, right neighbor is `nums[2] = 2`. Since `1 <= 2`, not good.
     - `nums[1] = 3`: No left neighbor, right neighbor is `nums[3] = 1`. Since `3 > 1`, it's good.
     - `nums[2] = 2`: Left neighbor is `nums[0] = 1`, right neighbor is `nums[4] = 5`. Since `2 <= 5`, not good.
     - `nums[3] = 1`: Left neighbor is `nums[1] = 3`, no right neighbor. Since `1 <= 3`, not good.
     - `nums[4] = 5`: Left neighbor is `nums[2] = 2`, no right neighbor. Since `5 > 2`, it's good.
     - `nums[5] = 4`: Left neighbor is `nums[3] = 1`, no right neighbor. Since `4 > 1`, it's good.
   - Sum = 3 + 5 + 4 = 12

## Solution

1. **Initialize**: Start with sum `s = 0` and get array length `n`

2. **Iterate through each element**: For each index `i` and value `val`:
   - Assume the element is good (`check = True`)
   
3. **Check left neighbor**: If `i - k >= 0` (left neighbor exists):
   - If `val <= nums[i - k]`, the element is not good (`check = False`)
   
4. **Check right neighbor**: If `i + k < n` (right neighbor exists):
   - If `val <= nums[i + k]`, the element is not good (`check = False`)

5. **Add to sum**: If `check` is still `True`, add `val` to the sum

6. **Return**: Return the total sum of all good elements

**Time Complexity**: O(n) - single pass through the array
**Space Complexity**: O(1) - only using constant extra space

**Key Points**:
- The algorithm uses a flag-based approach to track if an element is good
- It checks both conditions sequentially and sets the flag to False if any condition fails
- Only elements that pass both checks (or don't need to be checked) are added to the sum
- The solution handles edge cases naturally by checking index bounds before comparison

# Tags
Array, Simulation, Implementation

