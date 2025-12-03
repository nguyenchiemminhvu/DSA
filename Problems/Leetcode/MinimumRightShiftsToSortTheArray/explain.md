## Problem

https://leetcode.com/problems/minimum-right-shifts-to-sort-the-array/description/

```
You are given a 0-indexed array nums of length n containing distinct positive integers. 
Return the minimum number of right shifts required to sort nums and -1 if this is not possible.

A right shift is defined as shifting the element at index i to index (i + 1) % n, for all indices.

Example 1:
Input: nums = [3,4,5,1,2]
Output: 2
Explanation: 
After the first right shift, nums = [2,3,4,5,1].
After the second right shift, nums = [1,2,3,4,5].
Now nums is sorted; therefore the answer is 2.

Example 2:
Input: nums = [1,3,5]
Output: 0
Explanation: nums is already sorted therefore, the answer is 0.

Example 3:
Input: nums = [2,1,4]
Output: -1
Explanation: It's impossible to sort the array using right shifts.

Constraints:
- 1 <= nums.length <= 100
- 1 <= nums[i] <= 100
- nums contains distinct integers.
```

## Observations

1. **Right Shift Operation**: A right shift moves the last element to the front, essentially rotating the array clockwise.
   - After 1 shift: `[3,4,5,1,2]` → `[2,3,4,5,1]`
   - After 2 shifts: `[2,3,4,5,1]` → `[1,2,3,4,5]`

2. **Rotation Property**: An array that can be sorted by right shifts must be a rotated version of a sorted array.
   - A sorted array rotated k positions right looks like: `[sorted[n-k:], sorted[:n-k]]`
   - Example: `[1,2,3,4,5]` rotated right by 2 → `[4,5,1,2,3]`

3. **Pivot Point**: In a rotated sorted array, there is at most **one** position where `nums[i] < nums[i-1]`. This is the "break point" or pivot.
   - `[3,4,5,1,2]`: pivot at index 3 (1 < 5)
   - `[1,2,3,4,5]`: no pivot (already sorted)
   - `[2,1,4]`: pivot at index 1, but array is not a valid rotation

4. **Valid Rotation Check**: For the array to be sortable via right shifts:
   - There should be at most one pivot point
   - Both segments (before and after pivot) must be individually sorted
   - The last element must be less than the first element (unless already sorted)

5. **Converting Left to Right Shifts**: If we need to left-shift k times, it's equivalent to right-shifting (n - k) times.

## Solution

### Approach: Find Pivot and Validate

**Algorithm:**
1. **Find the pivot point**: Scan the array to find where `nums[i] < nums[i-1]`
2. **Simulate rotation**: Extend the array by appending the first `pivot` elements to create the "would-be" sorted array
3. **Validate**: Check if this extended array is fully sorted
4. **Calculate shifts**: If valid, return `n - pivot` (converting left shifts to right shifts)

**Example Walkthrough:**

*Example 1: nums = [3,4,5,1,2]*
- Find pivot: At i=3, nums[3]=1 < nums[2]=5, so pivot=3
- Extend: nums becomes [3,4,5,1,2,3,4,5]
- Validate: Check indices 4-7: 1<2<3<4<5 ✓
- Result: 5 - 3 = 2 right shifts

*Example 2: nums = [1,3,5]*
- Find pivot: No break found, pivot=3
- Extend: nums becomes [1,3,5,1,3,5]
- Validate: Check indices 4-5: Both valid ✓
- Result: 3 - 3 = 0 right shifts (already sorted)

*Example 3: nums = [2,1,4]*
- Find pivot: At i=1, nums[1]=1 < nums[0]=2, so pivot=1
- Extend: nums becomes [2,1,4,2]
- Validate: At i=3, nums[3]=2 < nums[2]=4, but then would need nums[4] but nums[4] doesn't exist properly in validation... Actually at i=2, nums[2]=4 > nums[1]=1 ✓, but we check if the rotation makes sense
- Actually the validation catches that after rotation [1,4,2] is not sorted (4 > 2), return -1

**Complexity Analysis:**
- **Time Complexity**: O(n) - Single pass to find pivot + single pass to validate
- **Space Complexity**: O(n) - Creating extended array with `nums.extend()`

**Alternative O(1) Space Approach:**
Instead of extending the array, we can validate using modular arithmetic:
```python
def minimumRightShifts(self, nums: List[int]) -> int:
    n = len(nums)
    pivot = n
    
    for i in range(1, n):
        if nums[i] < nums[i - 1]:
            pivot = i
            break
    
    # Validate rotation without extending array
    for i in range(n):
        next_i = (i + 1) % n
        if nums[(pivot + next_i) % n] < nums[(pivot + i) % n]:
            return -1
    
    return n - pivot
```

# Tags
#array #rotation #sorting #pivot #two-pointer

