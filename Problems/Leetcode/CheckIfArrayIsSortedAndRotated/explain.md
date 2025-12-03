## Problem

https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/description/

Given an array `nums`, return `true` if the array was originally sorted in non-decreasing order, then rotated some number of positions (including zero). Otherwise, return `false`.

**Note:** An array A rotated by x positions results in an array B of the same length such that `B[i] == A[(i+x) % A.length]` for every valid index i.

**Constraints:**
- `1 <= nums.length <= 100`
- `1 <= nums[i] <= 100`
- There may be duplicates in the original array

**Examples:**

```
Input: nums = [3,4,5,1,2]
Output: true
Explanation: [1,2,3,4,5] is the original sorted array.
You can rotate the array by x = 2 positions to begin on the element of value 3: [3,4,5,1,2].

Input: nums = [2,1,3,4]
Output: false
Explanation: There is no sorted array once rotated that can make nums.

Input: nums = [1,2,3]
Output: true
Explanation: [1,2,3] is the original sorted array.
You can rotate the array by x = 0 positions (i.e. no rotation) to make nums.
```

## Observations

1. **Rotation Point (Pivot)**: In a rotated sorted array, there's at most one position where `nums[i] < nums[i-1]`. This is the rotation point where the array "breaks" its sorted order.

2. **Valid Rotated Array Properties**:
   - If the array is sorted and not rotated: no breaks (pivot = n)
   - If the array is sorted and rotated: exactly one break where the rotation occurred
   - If there are 2+ breaks: the array cannot be a rotated sorted array

3. **Key Insight**: After finding the pivot, we can conceptually "unrotate" the array by extending it with elements `[0:pivot]`. Then we verify that this reconstructed sequence is sorted.

4. **Edge Cases**:
   - Array with all same elements: `[1,1,1]` → valid (0 breaks)
   - Array with duplicates: `[3,3,1,2,3]` → need to check carefully
   - Single element or already sorted: always valid

## Solution

### Approach: Find Pivot and Validate

**Algorithm:**
1. Find the rotation pivot by scanning for the first position where `nums[i] < nums[i-1]`
2. If no such position exists, the array is already sorted (return true)
3. Extend the array with elements before the pivot: `nums.extend(nums[0:pivot])`
4. Verify that the extended portion is sorted
5. If we find another break in the extended portion, return false

**Time Complexity:** O(n) - we scan the array twice at most  
**Space Complexity:** O(n) - we extend the array with up to n elements

```python
class Solution:
    def check(self, nums: List[int]) -> bool:
        n = len(nums)
        pivot = n  # default: no rotation
        
        # Step 1: Find the rotation point (pivot)
        for i in range(1, n):
            if nums[i] < nums[i - 1]:
                pivot = i
                break
        
        # Step 2: Extend array to simulate "unrotation"
        # Conceptually: [3,4,5,1,2] + [3,4,5] = [3,4,5,1,2,3,4,5]
        nums.extend(nums[0:pivot])
        
        # Step 3: Verify the extended portion is sorted
        for i in range(pivot + 1, len(nums)):
            if nums[i] < nums[i - 1]:
                return False  # Found a second break - invalid
        
        return True
```

**Example Walkthrough:**

For `nums = [3,4,5,1,2]`:
- Find pivot: at index 3 (value 1 < value 5)
- Extend: `[3,4,5,1,2] + [3,4,5]` = `[3,4,5,1,2,3,4,5]`
- Check from index 4: `1→2→3→4→5` all sorted ✓
- Return `true`

For `nums = [2,1,3,4]`:
- Find pivot: at index 1 (value 1 < value 2)
- Extend: `[2,1,3,4] + [2]` = `[2,1,3,4,2]`
- Check from index 2: `1→3` (ok), `3→4` (ok), `4→2` ✗ (break!)
- Return `false`

### Alternative Approach (More Space Efficient):

Instead of extending the array, count the number of breaks:

```python
def check(self, nums: List[int]) -> bool:
    breaks = 0
    n = len(nums)
    
    for i in range(n):
        if nums[i] > nums[(i + 1) % n]:
            breaks += 1
    
    return breaks <= 1
```

This approach uses O(1) space and simply counts discontinuities. A valid rotated sorted array has at most 1 break.

# Tags

`Array` `Two Pointers` `Rotation` `Sorting` `Easy`

