## Problem

https://leetcode.com/problems/3sum/description/

```
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.

Example 2:

Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.

Example 3:

Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.

Constraints:

3 <= nums.length <= 3000
-105 <= nums[i] <= 105
```

## Observations

1. **Brute Force Approach**: A naive solution would check all possible triplets using three nested loops, resulting in O(n³) time complexity - too slow for the given constraints.

2. **Sorting Benefit**: By sorting the array first, we can:
   - Use the two-pointer technique efficiently
   - Skip duplicate elements easily
   - Apply early termination when the current number is positive (since sorted array means all remaining numbers are also positive)

3. **Reduction to Two Sum**: After fixing one element, the problem reduces to finding two numbers that sum to the negative of the fixed element - this is the classic Two Sum problem that can be solved with two pointers in O(n) time.

4. **Duplicate Handling**: The problem requires unique triplets, so we need to:
   - Skip duplicate values for the first element (outer loop)
   - Skip duplicate values for the left and right pointers when we find a valid triplet

5. **Early Termination**: If the current element is positive, we can break early because all subsequent elements will also be positive (array is sorted), making it impossible to find a sum of zero.

## Solution

### Approach: Sorting + Two Pointers

**Algorithm Steps:**

1. **Sort the array** - O(n log n)
   - Enables two-pointer technique
   - Helps identify and skip duplicates

2. **Fix the first element** - Iterate through the array
   - For each position `i`, find pairs `(l, r)` where `nums[i] + nums[l] + nums[r] = 0`
   - Skip if current element is the same as previous (avoid duplicate triplets)
   - Break if `nums[i] > 0` (optimization: no positive sum possible)

3. **Two-pointer search** for remaining two elements:
   - Initialize `l = i + 1` (left pointer) and `r = n - 1` (right pointer)
   - Calculate sum: `s = nums[i] + nums[l] + nums[r]`
   - If `s < 0`: move left pointer right (need larger values)
   - If `s > 0`: move right pointer left (need smaller values)
   - If `s == 0`: found a triplet!
     - Add to result
     - Skip all duplicate values at left pointer
     - Skip all duplicate values at right pointer
     - Move both pointers inward

**Example Walkthrough:**

Input: `nums = [-1, 0, 1, 2, -1, -4]`

After sorting: `[-4, -1, -1, 0, 1, 2]`

- **i = 0** (nums[i] = -4):
  - l = 1, r = 5: sum = -4 + (-1) + 2 = -3 (< 0, l++)
  - l = 2, r = 5: sum = -4 + (-1) + 2 = -3 (< 0, l++)
  - l = 3, r = 5: sum = -4 + 0 + 2 = -2 (< 0, l++)
  - l = 4, r = 5: sum = -4 + 1 + 2 = -1 (< 0, l++)
  - l = 5, r = 5: l >= r, exit

- **i = 1** (nums[i] = -1):
  - l = 2, r = 5: sum = -1 + (-1) + 2 = 0 ✓ → `[-1, -1, 2]`
  - Skip duplicates, move pointers
  - l = 3, r = 4: sum = -1 + 0 + 1 = 0 ✓ → `[-1, 0, 1]`

- **i = 2** (nums[i] = -1): Skip (duplicate of nums[1])

- **i = 3** (nums[i] = 0): Continue search...

Result: `[[-1, -1, 2], [-1, 0, 1]]`

**Complexity Analysis:**

- **Time Complexity**: O(n²)
  - Sorting: O(n log n)
  - Outer loop: O(n)
  - Inner two-pointer search: O(n)
  - Overall: O(n log n) + O(n²) = O(n²)

- **Space Complexity**: O(1) or O(n)
  - O(1) extra space if we don't count the output array
  - O(n) for sorting (depending on the sorting algorithm used)
  - The result array doesn't count toward space complexity

**Key Optimizations:**

1. **Early termination**: Break when `nums[i] > 0`
2. **Skip duplicates**: Avoid processing the same value multiple times
3. **Two pointers**: O(n) search instead of O(n²) nested loop

## Tags

array, two pointers