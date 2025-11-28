## Problem

https://leetcode.com/problems/semi-ordered-permutation/

```
You are given a 0-indexed permutation of n integers nums.

A permutation is called semi-ordered if the first number equals 1 and the last number equals n. 
You can perform the below operation as many times as you want until you make nums a semi-ordered permutation:
- Pick two adjacent elements in nums, then swap them.

Return the minimum number of operations to make nums a semi-ordered permutation.

Constraints:
- 2 <= nums.length == n <= 50
- 1 <= nums[i] <= 50
- nums is a permutation
```

## Observations

1. **Goal**: Move the minimum element (1) to the front and maximum element (n) to the back using adjacent swaps
2. **Key Insight**: Since we can only swap adjacent elements, this is essentially a bubble sort scenario
3. **Movement Cost**:
   - Moving min to front: requires `index_of_min` swaps (each swap moves it one position left)
   - Moving max to back: requires `(n - 1 - index_of_max)` swaps (each swap moves it one position right)
4. **Edge Case**: If min appears before max initially, when we move min to the front, max's index doesn't change. But if min appears after max initially, moving min left will also shift max one position to the right, saving us 1 swap
5. **Optimization**: We don't actually need to perform the swaps; we can calculate the count directly

## Solution

**Time Complexity**: O(n²) - Finding min/max is O(n), swapping can be O(n), and we do this twice  
**Space Complexity**: O(1) - Only using constant extra space

### Alternative solution: Direct Calculation (Optimized)
```python
class Solution:
    def semiOrderedPermutation(self, nums: List[int]) -> int:
        n = len(nums)
        min_idx = nums.index(min(nums))
        max_idx = nums.index(max(nums))
        
        # Calculate swaps needed
        swaps = min_idx + (n - 1 - max_idx)
        
        # If min is after max, they'll cross during movement, saving 1 swap
        if min_idx > max_idx:
            swaps -= 1
        
        return swaps
```

**Time Complexity**: O(n) - Two passes to find min and max indices  
**Space Complexity**: O(1) - Only using constant extra space

**Explanation**:
- `min_idx`: number of swaps to move min to position 0
- `(n - 1 - max_idx)`: number of swaps to move max to position n-1
- If `min_idx > max_idx`: when moving min left, it will pass through max's position, effectively moving max one position right for free, so we subtract 1

# Tags
`Array`, `Greedy`, `Simulation`, `Two Pointers`

