## Problem

https://leetcode.com/problems/absolute-difference-between-maximum-and-minimum-k-elements/description/

```
You are given an integer array nums and an integer k.

Find the absolute difference between:
- the sum of the k largest elements in the array; and
- the sum of the k smallest elements in the array.

Return an integer denoting this difference.

Example 1:
Input: nums = [5,2,2,4], k = 2
Output: 5
Explanation:
The k = 2 largest elements are 4 and 5. Their sum is 4 + 5 = 9.
The k = 2 smallest elements are 2 and 2. Their sum is 2 + 2 = 4.
The absolute difference is abs(9 - 4) = 5.

Example 2:
Input: nums = [100], k = 1
Output: 0
Explanation:
The largest element is 100.
The smallest element is 100.
The absolute difference is abs(100 - 100) = 0.

Constraints:
- 1 <= n == nums.length <= 100
- 1 <= nums[i] <= 100
- 1 <= k <= n
```

## Observations

1. **Need to identify k largest and k smallest elements**: The problem requires us to find two separate groups of elements and compute their sums.

2. **Sorting simplifies the task**: Once the array is sorted in ascending order:
   - The first k elements are the k smallest
   - The last k elements are the k largest

3. **Array size is small (max 100 elements)**: This means sorting with O(n log n) time complexity is perfectly acceptable.

4. **Elements can be duplicates**: The problem allows duplicate values, which doesn't affect our approach since we're just summing k elements from each end.

5. **Edge case handling**: When k equals n (all elements), or when all elements are the same, the difference would be 0.

## Solution

```python
class Solution:
    def absDifference(self, nums: List[int], k: int) -> int:
        nums.sort()
        return abs(sum(nums[len(nums) - k:]) - sum(nums[:k]))
```

**Algorithm:**

1. **Sort the array** in ascending order: `nums.sort()`
   - Time complexity: O(n log n)
   - After sorting, smaller elements are at the beginning and larger elements are at the end

2. **Extract k smallest elements**: `nums[:k]`
   - These are the first k elements after sorting
   - For example, if nums = [2, 2, 4, 5] and k = 2, we get [2, 2]

3. **Extract k largest elements**: `nums[len(nums) - k:]`
   - These are the last k elements after sorting
   - For the same example, we get [4, 5]

4. **Calculate the absolute difference**:
   - Sum the k largest: `sum(nums[len(nums) - k:])`
   - Sum the k smallest: `sum(nums[:k])`
   - Return the absolute difference: `abs(sum_largest - sum_smallest)`

**Time Complexity:** O(n log n) due to sorting, where n is the length of the array.

**Space Complexity:** O(1) if we consider the sorting to be in-place (Python's sort() is in-place). Otherwise, O(n) for the sorting algorithm's internal space.

**Why this works:**
- Sorting guarantees that we can access the k smallest and k largest elements by simple array slicing
- Since the k largest elements will always have a sum greater than or equal to the k smallest elements (after sorting), the difference is always non-negative, but we use `abs()` for safety
- The approach is straightforward and leverages Python's built-in functions for clean, readable code

# Tags

