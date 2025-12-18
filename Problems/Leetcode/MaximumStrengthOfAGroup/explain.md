## Problem

https://leetcode.com/problems/maximum-strength-of-a-group/description/

You are given a 0-indexed integer array `nums` representing the score of students in an exam. The teacher would like to form one **non-empty** group of students with **maximal strength**, where the strength of a group of students of indices `i0, i1, i2, ... , ik` is defined as `nums[i0] * nums[i1] * nums[i2] * ... * nums[ik]`.

Return the **maximum strength** of a group the teacher can create.

**Example 1:**
```
Input: nums = [3,-1,-5,2,5,-9]
Output: 1350
Explanation: One way to form a group of maximal strength is to group the students at indices [0,2,3,4,5]. 
Their strength is 3 * (-5) * 2 * 5 * (-9) = 1350, which we can show is optimal.
```

**Example 2:**
```
Input: nums = [-4,-5,-4]
Output: 20
Explanation: Group the students at indices [0, 1]. Then, we'll have a resulting strength of 20. 
We cannot achieve greater strength.
```

**Constraints:**
- `1 <= nums.length <= 13`
- `-9 <= nums[i] <= 9`

## Observations

1. **Product Behavior with Signs:**
   - Positive × Positive = Positive (increases value)
   - Negative × Negative = Positive (increases value if both are large in magnitude)
   - Positive × Negative = Negative (decreases value)
   - Any product with 0 = 0

2. **Key Insights:**
   - To maximize the product, we generally want to include:
     - All positive numbers
     - An even number of negative numbers (pairs cancel the negative sign)
   - We should avoid including 0 unless it's the only element or helps avoid a negative result
   - If we have an odd number of negative numbers, we should exclude the one with smallest absolute value

3. **Edge Cases:**
   - Single element array: must return that element (even if negative or zero)
   - All negative numbers: take the two largest (smallest magnitude) negatives, or just the largest if only one
   - Mix of positive, negative, and zero: carefully select to maximize product

4. **Constraint Analysis:**
   - Array length ≤ 13: small enough for brute force approach (2^13 = 8192 subsets)
   - Values are small (-9 to 9): no overflow concerns with reasonable products

## Solution

### Approach: Bit Masking (Brute Force)

The solution uses **bit manipulation** to enumerate all possible non-empty subsets of the array and finds the maximum product among them.

**Algorithm:**
1. Handle edge case: if array has only one element, return it
2. Initialize result to negative infinity
3. Iterate through all possible subsets using bit masks from 1 to 2^n - 1
   - Each bit in the mask represents whether to include the element at that index
   - `mask = 1` to `(1 << n) - 1` covers all non-empty subsets
4. For each subset (mask):
   - Calculate the product of all elements in the subset
   - Check bit `i` using `(1 << i) & mask`
   - If bit is set, multiply the element at index `i` to the product
5. Update the maximum result

**Time Complexity:** O(2^n × n) where n is the length of the array
- We iterate through 2^n subsets
- For each subset, we iterate through n elements to check membership
- With n ≤ 13, this is 2^13 × 13 ≈ 106,000 operations (acceptable)

**Space Complexity:** O(1) - only using a few variables

**Code Walkthrough:**
```python
class Solution:
    def maxStrength(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 1:
            return nums[0]  # Edge case: single element
        
        res = float('-inf')  # Initialize to negative infinity
        
        # Iterate through all non-empty subsets
        for mask in range(1, 1 << n):  # 1 to 2^n - 1
            p = 1  # Product of current subset
            
            # Check each bit position
            for i in range(n):
                if (1 << i) & mask:  # If i-th bit is set
                    p *= nums[i]
            
            res = max(res, p)  # Update maximum
        
        return res
```

**Why This Works:**
- By trying all possible subsets, we're guaranteed to find the optimal combination
- The bit mask elegantly represents subset membership
- Starting from mask=1 ensures we never consider an empty subset

**Example Trace (nums = [3, -1, -5, 2, 5, -9]):**
- mask = 111101 (binary) → indices [0,2,3,4,5] → 3×(-5)×2×5×(-9) = 1350 ✓
- This is the maximum among all 2^6 - 1 = 63 possible subsets

# Tags
`Array` `Bit Manipulation` `Backtracking` `Brute Force` `Product` `Subset Enumeration`

