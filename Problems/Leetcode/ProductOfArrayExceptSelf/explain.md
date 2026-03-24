## Problem

https://leetcode.com/problems/product-of-array-except-self/description/

Given an integer array `nums`, return an array `answer` such that `answer[i]` is equal to the product of all the elements of `nums` except `nums[i]`.

The product of any prefix or suffix of `nums` is guaranteed to fit in a 32-bit integer.

**Constraints:**
- You must write an algorithm that runs in **O(n) time** and **without using the division operation**
- 2 <= nums.length <= 10^5
- -30 <= nums[i] <= 30
- answer[i] is guaranteed to fit in a 32-bit integer

**Examples:**
- Input: nums = [1,2,3,4] → Output: [24,12,8,6]
- Input: nums = [-1,1,0,-3,3] → Output: [0,0,9,0,0]

## Observations

1. **Naive Approach**: One could compute the total product and divide by each element, but division is forbidden and doesn't handle zeros.

2. **prefix-suffix multiplication**: For each element at index `i`, the product of all other elements is:
   - product of all elements to the left (prefix) × product of all elements to the right (suffix)

3. **Two-pass approach**: 
   - First pass (left to right): compute prefix products for each position
   - Second pass (right to left): multiply suffix products into the result

4. **O(1) space complexity**: We can reuse the output array to store prefix products, then update it with suffix products in-place.

## Solution

```python
class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        n = len(nums)
        res = [1] * n
        
        # First pass: compute prefix products
        # res[i] = product of all elements to the left of i
        prefix = 1
        for i in range(n):
            res[i] = prefix
            prefix *= nums[i]
        
        # Second pass: multiply by suffix products
        # suffix = product of all elements to the right of i
        suffix = 1
        for i in range(n-1, -1, -1):
            res[i] *= suffix
            suffix *= nums[i]
        
        return res
```

**Step-by-step walkthrough with [1,2,3,4]:**

After prefix pass:
- res = [1, 1, 2, 6]  (products of all left elements)

After suffix pass:
- i=3: res[3] = 6 * 1 = 6, suffix = 4
- i=2: res[2] = 2 * 4 = 8, suffix = 12
- i=1: res[1] = 1 * 12 = 12, suffix = 24
- i=0: res[0] = 1 * 24 = 24, suffix = 24
- Result: [24, 12, 8, 6] ✓

**Time Complexity:** O(n) - two passes through the array
**Space Complexity:** O(1) - output array doesn't count as extra space

# Tags
- Array
- Prefix/Suffix Product
- Two-pass Algorithm

