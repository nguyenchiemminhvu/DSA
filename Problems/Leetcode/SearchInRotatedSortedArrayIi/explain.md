## Problem

https://leetcode.com/problems/search-in-rotated-sorted-array-ii/description/

```
There is an integer array nums sorted in non-decreasing order (not necessarily with distinct values).

Before being passed to your function, nums is rotated at an unknown pivot index k (0 <= k < nums.length) 
such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). 
For example, [0,1,2,4,4,4,5,6,6,7] might be rotated at pivot index 5 and become [4,5,6,6,7,0,1,2,4,4].

Given the array nums after the rotation and an integer target, return true if target is in nums, or false if it is not in nums.

You must decrease the overall operation steps as much as possible.

Example 1:
Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true

Example 2:
Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false

Constraints:
- 1 <= nums.length <= 5000
- -10^4 <= nums[i] <= 10^4
- nums is guaranteed to be rotated at some pivot.
- -10^4 <= target <= 10^4

Follow up: This problem is similar to Search in Rotated Sorted Array, but nums may contain duplicates. 
Would this affect the runtime complexity? How and why?
```

## Observations

1. **Rotated Sorted Array**: The array is originally sorted but rotated at an unknown pivot point. This creates two sorted subarrays.

2. **Duplicates Allowed**: Unlike the original problem, this version allows duplicate values, which complicates the binary search approach.

3. **Binary Search Challenge**: The presence of duplicates can make it difficult to determine which half of the array to search:
   - When `nums[left] == nums[mid] == nums[right]`, we cannot definitively determine which side is sorted
   - Example: `[1,1,1,3,1]` - we can't tell if the rotation point is on the left or right

4. **Key Detection Strategy**: 
   - Check if `nums[right] <= nums[left]` to detect if there's a rotation in the current range
   - If no rotation detected (`nums[right] > nums[left]`), the range is fully sorted, apply standard binary search
   - If rotation exists, recursively search both halves

5. **Worst Case Complexity**: Due to duplicates, worst-case time complexity degrades to O(n) when we need to search both halves repeatedly (e.g., all elements are the same except one).

## Solution

The solution uses a modified binary search approach with recursion:

```python
class Solution:
    def search(self, nums: List[int], target: int) -> bool:
        def binary_search(nums: List[int], target: int, left: int, right: int) -> bool:
            if left > right:
                return False
            
            mid = left + (right - left) // 2
            
            # Target found at mid
            if target == nums[mid]:
                return True
            
            # Check if there's a rotation in current range
            if nums[right] <= nums[left]:
                # Rotation exists: search both halves
                found_left = binary_search(nums, target, left, mid - 1)
                if found_left:
                    return found_left
                else:
                    return binary_search(nums, target, mid + 1, right)
            else:
                # No rotation: standard binary search on sorted array
                if target > nums[mid]:
                    return binary_search(nums, target, mid + 1, right)
                else:
                    return binary_search(nums, target, left, mid - 1)
            
            return False
        
        return binary_search(nums, target, 0, len(nums) - 1)
```

**Algorithm Explanation**:

1. **Base Case**: If `left > right`, search space is exhausted, return False

2. **Calculate Mid**: Use `left + (right - left) // 2` to avoid integer overflow

3. **Check Mid**: If target found at mid, return True immediately

4. **Rotation Detection**: 
   - If `nums[right] <= nums[left]`: rotation exists in current range
     - Recursively search left half first
     - If not found, search right half
   - If `nums[right] > nums[left]`: range is sorted
     - Apply standard binary search logic

5. **Standard Binary Search** (when sorted):
   - If `target > nums[mid]`: search right half
   - If `target < nums[mid]`: search left half

**Time Complexity**: 
- Best/Average case: O(log n) when rotation point is quickly identified
- Worst case: O(n) when duplicates force searching both halves repeatedly

**Space Complexity**: O(log n) to O(n) for recursion stack

# Tags
#binary-search #array #rotated-array #duplicates #divide-and-conquer #recursion

