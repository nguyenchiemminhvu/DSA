## Problem

https://leetcode.com/problems/shortest-unsorted-continuous-subarray/description/

```
Given an integer array nums, you need to find one continuous subarray such that if you only sort this subarray in non-decreasing order, then the whole array will be sorted in non-decreasing order.

Return the shortest such subarray and output its length.

Example 1:

Input: nums = [2,6,4,8,10,9,15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.

Example 2:

Input: nums = [1,2,3,4]
Output: 0

Example 3:

Input: nums = [1]
Output: 0

Constraints:

1 <= nums.length <= 104
-105 <= nums[i] <= 105
 

Follow up: Can you solve it in O(n) time complexity?
```

## Observations

1. **Key Insight**: If we compare the original array with its sorted version, the unsorted subarray is bounded by the first and last positions where elements differ.

2. **Edge Cases**: 
   - If the array is already sorted, return 0
   - Single element arrays are always sorted

3. **Approach Logic**: We can use comparison with sorted array or find elements that violate the sorted property.

4. **Optimal Insight**: In a properly sorted array:
   - Every element should be ≥ all elements to its left
   - Every element should be ≤ all elements to its right

## Solution

### Approach 1: Sorting Comparison (O(n log n))

```python
def findUnsortedSubarray(self, nums: List[int]) -> int:
    temp = sorted([val for val in nums])  # O(n log n)
    l = len(nums)  # Start with invalid left boundary
    r = -1         # Start with invalid right boundary
    
    # Find leftmost difference
    for i in range(0, len(nums)):
        if nums[i] != temp[i]:
            l = i
            break
    
    # Find rightmost difference  
    for i in range(len(nums) - 1, -1, -1):
        if nums[i] != temp[i]:
            r = i
            break
    
    return 0 if l > r else r - l + 1  # Handle already sorted case
```

**Time Complexity**: O(n log n) due to sorting  
**Space Complexity**: O(n) for the sorted copy

### Approach 2: Two-Pass O(n) Solution (Optimal)

```python
def findUnsortedSubarray(self, nums: List[int]) -> int:
    n = len(nums)
    left = n  # rightmost position of out-of-order element from left
    right = -1  # leftmost position of out-of-order element from right
    
    # Forward pass: find elements smaller than max seen so far
    max_seen = float('-inf')
    for i in range(n):
        if nums[i] >= max_seen:
            max_seen = nums[i]
        else:
            right = i  # This element is out of place
    
    # Backward pass: find elements larger than min seen so far
    min_seen = float('inf')
    for i in range(n-1, -1, -1):
        if nums[i] <= min_seen:
            min_seen = nums[i]
        else:
            left = i  # This element is out of place
    
    return max(0, right - left + 1)
```

**Time Complexity**: O(n)  
**Space Complexity**: O(1)

### Approach 3: Stack-based Solution

```python
def findUnsortedSubarray(self, nums: List[int]) -> int:
    stack = []
    left = len(nums)
    right = -1
    
    # Find left boundary using increasing stack
    for i in range(len(nums)):
        while stack and nums[stack[-1]] > nums[i]:
            left = min(left, stack.pop())
        stack.append(i)
    
    stack.clear()
    
    # Find right boundary using decreasing stack
    for i in range(len(nums)-1, -1, -1):
        while stack and nums[stack[-1]] < nums[i]:
            right = max(right, stack.pop())
        stack.append(i)
    
    return max(0, right - left + 1)
```

**Time Complexity**: O(n)  
**Space Complexity**: O(n)

## Algorithm Explanation

**Example**: `nums = [2,6,4,8,10,9,15]`

1. **Sorting approach**: Compare with `[2,4,6,8,9,10,15]`
   - First difference at index 1 (6 vs 4)
   - Last difference at index 5 (9 vs 10)
   - Length: 5 - 1 + 1 = 5

2. **O(n) approach**:
   - Forward pass: max_seen tracks maximum, right marks violations
   - Backward pass: min_seen tracks minimum, left marks violations
   - Elements 6,4,8,10,9 need reordering

## Tags

array, greedy, two-pointers, stack