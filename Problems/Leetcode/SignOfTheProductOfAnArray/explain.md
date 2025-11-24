## Problem

https://leetcode.com/problems/sign-of-the-product-of-an-array/description/

```
Implement a function signFunc(x) that returns:

1 if x is positive.
-1 if x is negative.
0 if x is equal to 0.
You are given an integer array nums. Let product be the product of all values in the array nums.

Return signFunc(product).

Example 1:

Input: nums = [-1,-2,-3,-4,3,2,1]
Output: 1
Explanation: The product of all values in the array is 144, and signFunc(144) = 1

Example 2:

Input: nums = [1,5,0,2,-3]
Output: 0
Explanation: The product of all values in the array is 0, and signFunc(0) = 0

Example 3:

Input: nums = [-1,1,-1,1,-1]
Output: -1
Explanation: The product of all values in the array is -1, and signFunc(-1) = -1

Constraints:

1 <= nums.length <= 1000
-100 <= nums[i] <= 100
```

## Observations

1. **Key insight**: We don't need to calculate the actual product - we only need the sign of the product.
2. **Zero handling**: If any number in the array is 0, the entire product will be 0.
3. **Sign rules**: The sign of a product depends only on the count of negative numbers:
   - Even count of negatives → positive product
   - Odd count of negatives → negative product
4. **Overflow prevention**: By avoiding actual multiplication, we prevent potential integer overflow issues.
5. **Efficiency**: O(1) space complexity and O(n) time complexity with early termination when 0 is found.

## Solution

1. Initialize counters for negative and positive numbers
2. Iterate through the array:
   - If we find a 0, immediately return 0 (product will be 0)
   - Count negative numbers
   - Count positive numbers (optional - not used in final calculation)
3. Use bitwise AND (`count_neg & 1`) to check if count of negatives is odd:
   - If odd number of negatives: product is negative → return -1
   - If even number of negatives: product is positive → return 1

**Time Complexity:** O(n) where n is the length of the array
**Space Complexity:** O(1) - only using constant extra space

**Key optimizations:**
- Early termination when 0 is found
- No actual multiplication (avoids overflow)
- Bitwise operation for even/odd check is slightly faster than modulo

# Tags
Array, Math, Simulation

