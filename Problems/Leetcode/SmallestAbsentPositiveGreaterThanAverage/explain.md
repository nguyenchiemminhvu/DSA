## Problem

https://leetcode.com/problems/smallest-absent-positive-greater-than-average/description/

```
You are given an integer array nums.

Return the smallest absent positive integer in nums such that it is strictly greater 
than the average of all elements in nums.

The average of an array is defined as the sum of all its elements divided by the 
number of elements.

Example 1:
Input: nums = [3,5]
Output: 6
Explanation: The average of nums is (3 + 5) / 2 = 8 / 2 = 4.
The smallest absent positive integer greater than 4 is 6.

Example 2:
Input: nums = [-1,1,2]
Output: 3
Explanation: The average of nums is (-1 + 1 + 2) / 3 = 2 / 3 = 0.667.
The smallest absent positive integer greater than 0.667 is 3.

Example 3:
Input: nums = [4,-1]
Output: 2
Explanation: The average of nums is (4 + (-1)) / 2 = 3 / 2 = 1.50.
The smallest absent positive integer greater than 1.50 is 2.

Constraints:
- 1 <= nums.length <= 100
- -100 <= nums[i] <= 100
```

## Observations

1. **Average Calculation**: We need to compute the average of all elements. Since we're looking for integers, we can use integer division (`//` in Python).

2. **Positive Integer Constraint**: The result must be a positive integer, so even if the average is negative, we start searching from 1 (or the ceiling of the average if positive).

3. **Strictly Greater Than Average**: The result must be strictly greater than the average, not equal to it.

4. **Absent from Array**: The integer must not be present in the original array.

5. **Bounded Search Space**: Given the constraints (-100 ≤ nums[i] ≤ 100 and max length 100), the maximum possible average is 100. However, we need to find the smallest absent integer, so we don't need to search infinitely far.

6. **Set for Efficient Lookup**: Converting the array to a set allows O(1) lookup to check if a number exists in the array.

## Solution

1. **Calculate Average**: 
   - Compute `sum(nums) // len(nums)` for integer division
   - Use `max(0, ...)` to ensure we start from at least 0 (for positive integers)
   - This gives us the floor of the average

2. **Create Set**: 
   - Convert `nums` to a set for O(1) membership checking
   - This is crucial for efficient lookup in the next step

3. **Linear Search**:
   - Start from `avg + 1` (strictly greater than average)
   - Check each integer sequentially until we find one not in the set
   - The search bound of 1001 is more than sufficient given the constraints

4. **Return Result**:
   - Return the first integer that's not in the set
   - The fallback `return 0` should never be reached given the constraints

**Why This Works**:
- Since the array has at most 100 elements, and values range from -100 to 100, there are at most 100 distinct values
- Starting from the average and going upward, we're guaranteed to find a missing integer quickly
- The maximum average is 100, and with at most 100 distinct values, we'll find a gap well before 1001

**Time Complexity**: O(n + k) where n is the length of nums (for computing sum and creating set) and k is the number of iterations (typically very small, worst case ~200)

**Space Complexity**: O(n) for the set

# Tags
#array #hash-set #math #average #greedy

