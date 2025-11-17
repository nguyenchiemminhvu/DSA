## Problem

https://leetcode.com/problems/check-if-all-1s-are-at-least-length-k-places-away/description/

```
Given an binary array nums and an integer k, return true if all 1's are at least k places away from each other, otherwise return false.

Example 1:

Input: nums = [1,0,0,0,1,0,0,1], k = 2
Output: true
Explanation: Each of the 1s are at least 2 places away from each other.

Example 2:

Input: nums = [1,0,0,1,0,1], k = 2
Output: false
Explanation: The second 1 and third 1 are only one apart from each other.

Constraints:

1 <= nums.length <= 105
0 <= k <= nums.length
nums[i] is 0 or 1
```

## Observations

1. **Problem Understanding**: We need to check if every pair of consecutive 1's in the array has at least `k` 0's between them.

2. **Key Insight**: We don't need to track positions of 1's explicitly. Instead, we can count the number of 0's between consecutive 1's as we iterate through the array.

3. **Edge Cases**:
   - If there's only one 1 or no 1's in the array, the condition is automatically satisfied
   - The first 1 in the array doesn't need to be checked against any previous 1
   - We only need to verify the distance when we encounter a 1 (not when we encounter 0's)

4. **Counting Strategy**: 
   - Count consecutive 0's between 1's
   - When we find a 1, check if we have at least `k` 0's since the last 1
   - Reset the counter when we find a 1

## Solution

1. **Initialization**: `c0 = 0xFFFFFFFF` (a very large number)
   - This ensures the first 1 we encounter will always pass the check since `0xFFFFFFFF >= k` for any valid k

2. **Iteration**: For each element in the array:
   - If it's 0: increment the zero counter `c0`
   - If it's 1: 
     - Check if `c0 >= k` (enough zeros since last 1)
     - If not enough zeros, return `False`
     - Reset `c0 = 0` to start counting for the next sequence

3. **Why this works**:
   - The large initial value handles the first 1 elegantly
   - We only check the distance constraint when we encounter a 1
   - The counter accurately tracks zeros between consecutive 1's

**Time Complexity**: O(n) - single pass through the array
**Space Complexity**: O(1) - only using a constant amount of extra space

**Example Walkthrough**:
- `nums = [1,0,0,0,1,0,0,1], k = 2`
- Initial: `c0 = 0xFFFFFFFF`
- Index 0 (1): `c0 >= 2` ✓, reset `c0 = 0`
- Index 1-3 (0,0,0): `c0 = 3`
- Index 4 (1): `c0 = 3 >= 2` ✓, reset `c0 = 0`
- Index 5-6 (0,0): `c0 = 2`
- Index 7 (1): `c0 = 2 >= 2` ✓, reset `c0 = 0`
- Return `True`

# Tags

- Array
- Simulation
- Two Pointers

