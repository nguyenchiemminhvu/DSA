# Maximum Sum Circular Subarray

## Problem

https://leetcode.com/problems/maximum-sum-circular-subarray/description/

Given a **circular integer array** `nums` of length `n`, return the **maximum possible sum** of a non-empty subarray of `nums`.

A **circular array** means the end of the array connects to the beginning of the array. Formally:
- The next element of `nums[i]` is `nums[(i + 1) % n]`
- The previous element of `nums[i]` is `nums[(i - 1 + n) % n]`

A subarray may only include each element of the fixed buffer `nums` at most once. Formally, for a subarray `nums[i], nums[i + 1], ..., nums[j]`, there does not exist `i <= k1, k2 <= j` with `k1 % n == k2 % n`.

### Examples

**Example 1:**
```
Input: nums = [1,-2,3,-2]
Output: 3
Explanation: Subarray [3] has maximum sum 3.
```

**Example 2:**
```
Input: nums = [5,-3,5]
Output: 10
Explanation: Subarray [5,5] has maximum sum 5 + 5 = 10.
```

**Example 3:**
```
Input: nums = [-3,-2,-3]
Output: -2
Explanation: Subarray [-2] has maximum sum -2.
```

### Constraints

- `n == nums.length`
- `1 <= n <= 3 * 10^4`
- `-3 * 10^4 <= nums[i] <= 3 * 10^4`

---

## Observations

### Key Insight: Two Possible Cases

In a circular array, the maximum sum subarray can be in one of two forms:

1. **Non-wrapping subarray**: The subarray is contiguous and doesn't wrap around the array
   - Example: `[1, -2, 3, -2]` → subarray `[3]` with sum 3
   - This is the standard maximum subarray problem (Kadane's algorithm)

2. **Wrapping subarray**: The subarray wraps around from the end to the beginning
   - Example: `[5, -3, 5]` → subarray `[5, 5]` (wraps around) with sum 10
   - Think of it as: taking elements from the start AND from the end

### Critical Observation for Wrapping Case

If the maximum subarray wraps around, then:
- We're taking some elements from the beginning and some from the end
- The elements in the **middle** that we're NOT taking form a contiguous subarray
- To maximize the sum of elements we take, we need to **minimize** the sum of elements we skip

Therefore:
```
Maximum wrapping sum = Total sum - Minimum subarray sum
```

### Visual Representation

```
Non-wrapping:
[a, b, c, d, e, f]
    [----max----]

Wrapping:
[a, b, c, d, e, f]
[---]       [-----]  ← We take these
     [-----]         ← We skip this (minimum subarray)
```

### Edge Case: All Negative Numbers

If all numbers are negative:
- `ka_min` will be the sum of all elements (entire array is minimum)
- `sum(nums) - ka_min` would be 0
- But we need a non-empty subarray, so we return `ka_max` (the least negative number)
- The check `if ka_max < 0` handles this case

---

## Solution

### Algorithm: Modified Kadane's Algorithm

We run **two versions of Kadane's algorithm simultaneously**:

1. **Standard Kadane's** to find maximum subarray sum (`ka_max`)
2. **Inverted Kadane's** to find minimum subarray sum (`ka_min`)

Then we return:
```
max(ka_max, sum(nums) - ka_min)
```

### Implementation

```python
class Solution:
    def maxSubarraySumCircular(self, nums: List[int]) -> int:
        n = len(nums)
        
        # Initialize with first element
        cur_max = nums[0]  # Current maximum subarray sum ending at current position
        cur_min = nums[0]  # Current minimum subarray sum ending at current position
        ka_max = nums[0]   # Global maximum subarray sum
        ka_min = nums[0]   # Global minimum subarray sum
        
        # Process remaining elements
        for i in range(1, n):
            # Kadane's for maximum subarray
            cur_max = max(nums[i], cur_max + nums[i])
            ka_max = max(ka_max, cur_max)
            
            # Kadane's for minimum subarray
            cur_min = min(nums[i], cur_min + nums[i])
            ka_min = min(ka_min, cur_min)
        
        # Edge case: all negative numbers
        if ka_max < 0:
            return max(nums)
        
        # Return max of: non-wrapping sum OR wrapping sum
        return max(ka_max, sum(nums) - ka_min)
```

### Variables Explained

- **`cur_max`**: Maximum sum of subarray ending at current index
  - At each position, decide: start fresh with current element OR extend previous subarray
  - `cur_max = max(nums[i], cur_max + nums[i])`

- **`ka_max`**: Overall maximum subarray sum found so far (Kadane's max)
  - `ka_max = max(ka_max, cur_max)`

- **`cur_min`**: Minimum sum of subarray ending at current index
  - Similar logic but finding minimum
  - `cur_min = min(nums[i], cur_min + nums[i])`

- **`ka_min`**: Overall minimum subarray sum found so far (Kadane's min)
  - `ka_min = min(ka_min, cur_min)`

### Why This Works

**Case 1: Non-wrapping maximum**
- This is captured by `ka_max` (standard Kadane's algorithm)

**Case 2: Wrapping maximum**
- If we take elements wrapping around, we skip some middle portion
- To maximize what we take, minimize what we skip
- The skipped portion is found by `ka_min`
- So wrapping maximum = `sum(nums) - ka_min`

**Edge case handling:**
- If all numbers are negative, `ka_max < 0`
- `ka_min` would equal `sum(nums)` (entire array is minimum)
- `sum(nums) - ka_min = 0`, but we need non-empty subarray
- So we return `max(nums)` (the least negative element)

---

## Complexity Analysis

### Time Complexity: **O(n)**
- Single pass through the array to compute `ka_max` and `ka_min`
- Computing `sum(nums)` is O(n) but can be done in the same pass
- Overall: O(n)

### Space Complexity: **O(1)**
- Only using a constant number of variables
- No additional data structures

---

## Examples Walkthrough

### Example 1: `nums = [1, -2, 3, -2]`

| i | nums[i] | cur_max | ka_max | cur_min | ka_min |
|---|---------|---------|--------|---------|--------|
| 0 | 1       | 1       | 1      | 1       | 1      |
| 1 | -2      | -1      | 1      | -2      | -2     |
| 2 | 3       | 3       | 3      | -1      | -2     |
| 3 | -2      | 1       | 3      | -3      | -3     |

- `sum(nums) = 0`
- `ka_max = 3` (non-wrapping: [3])
- `sum(nums) - ka_min = 0 - (-3) = 3`
- Result: `max(3, 3) = 3` ✓

### Example 2: `nums = [5, -3, 5]`

| i | nums[i] | cur_max | ka_max | cur_min | ka_min |
|---|---------|---------|--------|---------|--------|
| 0 | 5       | 5       | 5      | 5       | 5      |
| 1 | -3      | 2       | 5      | -3      | -3     |
| 2 | 5       | 7       | 7      | 2       | -3     |

- `sum(nums) = 7`
- `ka_max = 7` (non-wrapping: [5, -3, 5])
- `sum(nums) - ka_min = 7 - (-3) = 10` (wrapping: [5, 5])
- Result: `max(7, 10) = 10` ✓

### Example 3: `nums = [-3, -2, -3]`

| i | nums[i] | cur_max | ka_max | cur_min | ka_min |
|---|---------|---------|--------|---------|--------|
| 0 | -3      | -3      | -3     | -3      | -3     |
| 1 | -2      | -2      | -2     | -5      | -5     |
| 2 | -3      | -5      | -2     | -8      | -8     |

- `ka_max = -2 < 0` → All negative case
- Return `max(nums) = -2` ✓

---

## Key Takeaways

1. **Circular array** → Think about wrapping vs non-wrapping cases
2. **Wrapping maximum** = `Total sum - Minimum subarray`
3. Run **both Kadane's max and min** simultaneously
4. Handle **all negative numbers** edge case
5. **O(n) time, O(1) space** - optimal solution

This problem elegantly combines:
- Kadane's algorithm (maximum subarray)
- Circular array thinking (wrapping consideration)
- Mathematical insight (complement of minimum is maximum in circular context)

---

# Tags

`#kadanes-algorithm` `#dynamic-programming` `#array` `#circular-array` `#medium`

