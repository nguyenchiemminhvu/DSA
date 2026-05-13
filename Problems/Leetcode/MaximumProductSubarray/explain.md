## Problem

https://leetcode.com/problems/maximum-product-subarray/description

Given an integer array `nums`, find a **contiguous subarray** that has the **largest product**, and return that product.

**Key Constraints:**
- A subarray must be contiguous (consecutive elements from the array)
- The product of a single element subarray equals that element
- Array length: 1 to 20,000 elements
- Element values: -10 to 10
- Answer fits in 32-bit integer

### Examples

**Example 1:**
```
Input: nums = [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.
```

**Example 2:**
```
Input: nums = [-2,0,-1]
Output: 0
Explanation: The result cannot be 2 because [-2,-1] is not contiguous in the original array.
The best subarray is [0], which gives 0.
```

**Example 3:**
```
Input: nums = [-2]
Output: -2
Explanation: Only one element, so return -2.
```

---

## Observations

### Why This Problem is Tricky

Unlike the **Maximum Sum Subarray** problem (Kadane's algorithm), this problem requires tracking **both minimum and maximum** products because:

1. **Negative numbers flip signs:** A small negative product (min) when multiplied by a negative number becomes a large positive product (max).
   - Example: `cur_min = -5`, new element = `-2` → result = `(-5) × (-2) = 10` (positive!)

2. **Zero breaks streaks:** A zero always resets the product to 0, which is often suboptimal.

3. **Single element matters:** We must consider each individual element as a subarray.

### Key Insight

At each position `i`, we maintain:
- **`cur_min`**: Minimum product ending at index `i` (could be very negative)
- **`cur_max`**: Maximum product ending at index `i` (could be very positive)
- **`res`**: Global maximum product seen so far

When processing `nums[i]`:
- If we multiply it by `cur_min` (negative), we might get a large positive
- If we multiply it by `cur_max` (positive), we might get a large positive
- If we take `nums[i]` alone, we start fresh from this element

We consider all three: `nums[i]`, `nums[i] * cur_min`, `nums[i] * cur_max`

---

## Solution

### Approach: Dynamic Programming (1D DP)

**Time Complexity:** O(n) — single pass through array  
**Space Complexity:** O(1) — only store two variables (cur_min, cur_max)

```python
class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        n = len(nums)
        res = nums[0]
        cur_min = cur_max = nums[0]
        
        for i in range(1, n):
            val = nums[i]
            # Compute new min and max with current element
            tmp_min = min(val, val * cur_min, val * cur_max)
            tmp_max = max(val, val * cur_min, val * cur_max)
            
            # Update state for next iteration
            cur_min, cur_max = tmp_min, tmp_max
            
            # Track global maximum
            res = max(res, tmp_max)
        
        return res
```

### Step-by-Step Walkthrough

**Example: `nums = [2, 3, -2, 4]`**

| i | val | cur_min | cur_max | Candidates (val, val*min, val*max) | New Min | New Max | res |
|---|-----|---------|---------|-------------------------------------|---------|---------|-----|
| 0 (init) | - | 2 | 2 | - | - | - | 2 |
| 1 | 3 | 2 | 2 | (3, 6, 6) | 3 | 6 | 6 |
| 2 | -2 | 3 | 6 | (-2, -6, -12) | -12 | -2 | 6 |
| 3 | 4 | -12 | -2 | (4, -48, -8) | -48 | 4 | 6 |

**Result: 6** ✓

**Why this works at i=2:**
- Previous: `cur_max = 6` (product [2,3])
- New element: `-2`
- `val * cur_max = (-2) × 6 = -12` (negative, not useful)
- `val = -2` alone is better than continuing the subarray
- But `val * cur_min = (-2) × 3 = -6` is also considered

The algorithm correctly identifies that continuing beyond the -2 yields no benefit.

### Alternative: Recursive with Memoization

The commented code in the solution shows the recursive approach:
- `F(i)` returns tuple `(min_product, max_product)` ending at index `i`
- State: At each position, track both min and max products possible
- Same logic, but with function call overhead

The **iterative approach is preferred** for O(1) space.

### Edge Cases Handled

1. **Single element:** `res = nums[0]` initialization, loop doesn't execute
2. **All negative:** Alternates between large negative and small products correctly
3. **Contains zero:** Zero resets streak, treated as starting fresh
4. **Mix of signs:** min/max flip handles all transitions

---

## Complexity Analysis

| Metric | Value |
|--------|-------|
| Time Complexity | O(n) - Single pass through array |
| Space Complexity | O(1) - Only constant extra variables |
| Optimal | Yes - Cannot do better than O(n) as we must examine all elements |

---

# Tags

#dynamic-programming #array #1d-dp #kadane-variant #greedy #product

