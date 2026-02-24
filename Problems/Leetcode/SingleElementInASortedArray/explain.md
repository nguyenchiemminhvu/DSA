## Problem

https://leetcode.com/problems/single-element-in-a-sorted-array/description/

```
You are given a sorted array consisting of only integers where every element appears exactly twice, 
except for one element which appears exactly once.

Return the single element that appears only once.

Your solution must run in O(log n) time and O(1) space.

Example 1:
Input: nums = [1,1,2,3,3,4,4,8,8]
Output: 2

Example 2:
Input: nums = [3,3,7,7,10,11,11]
Output: 10

Constraints:
- 1 <= nums.length <= 10^5
- 0 <= nums[i] <= 10^5
```

## Observations

1. **Paired Pattern**: Every element appears twice except one. This means the array has an odd length (2n + 1).

2. **Index Pattern Before Single Element**:
   - Pairs start at even indices: (0,1), (2,3), (4,5), ...
   - For any pair starting at even index `i`: nums[i] == nums[i+1]

3. **Index Pattern After Single Element**:
   - Once the single element appears, the pairing shifts
   - Pairs now start at odd indices
   - For any pair starting at even index `i` after the single: nums[i] == nums[i-1]

4. **Binary Search Applicability**:
   - The array is sorted and has a predictable pattern
   - We can use binary search to find where the pattern breaks
   - Time: O(log n), Space: O(1) ✓

5. **Key Insight**:
   - If we're at an even index and nums[mid] == nums[mid+1], the single element is to the right
   - If we're at an even index and nums[mid] != nums[mid+1], the single element is at mid or to the left

## Solution

### Approach: Binary Search with Even Index Alignment

The algorithm uses binary search but ensures we always check at even indices to maintain consistent comparison logic.

**Algorithm**:
1. Initialize `left = 0`, `right = n - 1`
2. While `left < right`:
   - Calculate `mid = left + (right - left) // 2`
   - **Align to even index**: If `mid` is odd, decrement it by 1
   - Check if `nums[mid] == nums[mid + 1]`:
     - **Yes**: The pair is intact, single element is to the right → `left = mid + 2`
     - **No**: The pair is broken, single element is at mid or left → `right = mid`
3. Return `nums[left]`

**Why align to even index?**
- By always checking at even indices, we maintain consistent logic
- If mid is odd and we compare nums[mid] with nums[mid+1], the logic would be inverted
- Adjusting odd mid to even simplifies the comparison

**Example Walkthrough** with `nums = [1,1,2,3,3,4,4,8,8]`:
```
Initial: left=0, right=8, length=9

Iteration 1:
  mid = 0 + (8-0)//2 = 4 (even, no adjustment)
  nums[4]=3, nums[5]=4 → not equal
  Single element is at or left of index 4
  right = 4

Iteration 2:
  mid = 0 + (4-0)//2 = 2 (even, no adjustment)
  nums[2]=2, nums[3]=3 → not equal
  Single element is at or left of index 2
  right = 2

Iteration 3:
  mid = 0 + (2-0)//2 = 1 (odd, adjust to 0)
  nums[0]=1, nums[1]=1 → equal
  Single element is to the right
  left = 0 + 2 = 2

Loop ends (left == right == 2)
Return nums[2] = 2 ✓
```

**Python Implementation**:
```python
class Solution:
    def singleNonDuplicate(self, nums: List[int]) -> int:
        n = len(nums)
        left = 0
        right = n - 1
        
        while left < right:
            mid = left + (right - left) // 2
            
            # Ensure mid is even for consistent comparison
            if mid & 1:  # if mid is odd
                mid -= 1
            
            # Check if the pair is intact
            if nums[mid] == nums[mid + 1]:
                # Single element is to the right
                left = mid + 2
            else:
                # Single element is at mid or to the left
                right = mid
        
        return nums[left]
```

**Complexity Analysis**:
- **Time**: O(log n) - Binary search halves the search space each iteration
- **Space**: O(1) - Only uses a constant amount of extra space

# Tags
`Binary Search` `Array` `Bit Manipulation`

