## Problem

https://leetcode.com/problems/get-maximum-in-generated-array/description/

You are given an integer `n`. A 0-indexed integer array `nums` of length `n + 1` is generated in the following way:

- `nums[0] = 0`
- `nums[1] = 1`
- `nums[2 * i] = nums[i]` when `2 <= 2 * i <= n`
- `nums[2 * i + 1] = nums[i] + nums[i + 1]` when `2 <= 2 * i + 1 <= n`

Return the **maximum** integer in the array `nums`.

### Examples

**Example 1:**
```
Input: n = 7
Output: 3
Explanation: According to the given rules:
  nums[0] = 0
  nums[1] = 1
  nums[(1 * 2) = 2] = nums[1] = 1
  nums[(1 * 2) + 1 = 3] = nums[1] + nums[2] = 1 + 1 = 2
  nums[(2 * 2) = 4] = nums[2] = 1
  nums[(2 * 2) + 1 = 5] = nums[2] + nums[3] = 1 + 2 = 3
  nums[(3 * 2) = 6] = nums[3] = 2
  nums[(3 * 2) + 1 = 7] = nums[3] + nums[4] = 2 + 1 = 3
Hence, nums = [0,1,1,2,1,3,2,3], and the maximum is max(0,1,1,2,1,3,2,3) = 3.
```

**Example 2:**
```
Input: n = 2
Output: 1
Explanation: nums = [0,1,1]. The maximum is max(0,1,1) = 1.
```

**Example 3:**
```
Input: n = 3
Output: 2
Explanation: nums = [0,1,1,2]. The maximum is max(0,1,1,2) = 2.
```

**Constraints:**
- `0 <= n <= 100`

## Observations

1. **Base Cases**: The array always starts with `nums[0] = 0` and `nums[1] = 1` (when `n >= 1`).

2. **Even Indices Pattern**: For even indices `i`, the value is copied from `nums[i // 2]`. This creates a relationship where even positions reference earlier positions in the array.

3. **Odd Indices Pattern**: For odd indices `i`, the value is the sum of two consecutive elements: `nums[i // 2] + nums[i // 2 + 1]`. This can potentially create larger values.

4. **Sequential Dependency**: Each element depends only on previously computed elements, making this suitable for a bottom-up dynamic programming approach.

5. **Maximum Tracking**: The maximum value could appear at any position in the array, so we need to check all elements.

6. **Array Growth**: The array grows sequentially from index 0 to n, and we can build it iteratively.

## Solution

### Approach: Dynamic Programming (Bottom-Up)

The solution uses a straightforward iterative approach to build the array according to the given rules.

**Algorithm:**

1. **Handle Edge Case**: If `n = 0`, return 0 immediately (array has only one element: [0]).

2. **Initialize Array**: Start with the base case `nums = [0, 1]`.

3. **Build Array Iteratively**: For each index `i` from 2 to n:
   - If `i` is **even**: `nums[i] = nums[i // 2]`
   - If `i` is **odd**: `nums[i] = nums[i // 2] + nums[i // 2 + 1]`

4. **Find Maximum**: After building the complete array, return the maximum value.

**Why This Works:**

The iteration proceeds from index 2 to n, ensuring that when we compute `nums[i]`, all required previous values (`nums[i // 2]` and `nums[i // 2 + 1]`) are already computed. Since `i >= 2`, we have `i // 2 >= 1` and `i // 2 + 1 <= i`, so all referenced indices are valid and already filled.

### Code Implementation

```python
class Solution:
    def getMaximumGenerated(self, n: int) -> int:
        # Edge case: if n is 0, the array is just [0]
        if n == 0:
            return 0
        
        # Initialize with base cases
        nums = [0, 1]
        
        # Build the array according to the rules
        for i in range(2, n + 1):
            if i % 2 == 0:
                # Even index: copy from nums[i // 2]
                nums.append(nums[i // 2])
            else:
                # Odd index: sum of nums[i // 2] and nums[i // 2 + 1]
                nums.append(nums[i // 2] + nums[i // 2 + 1])
        
        # Return the maximum value in the array
        return max(nums)
```

### Complexity Analysis

**Time Complexity: O(n)**
- We iterate through indices from 2 to n exactly once: O(n)
- Finding the maximum of the array: O(n)
- Total: O(n)

**Space Complexity: O(n)**
- We store an array of size n + 1
- No additional significant space is used

### Optimization: Track Maximum During Construction

We can optimize by tracking the maximum during array construction to avoid the final max() call:

```python
class Solution:
    def getMaximumGenerated(self, n: int) -> int:
        if n == 0:
            return 0
        
        nums = [0, 1]
        max_val = 1  # Track maximum as we build
        
        for i in range(2, n + 1):
            if i % 2 == 0:
                nums.append(nums[i // 2])
            else:
                nums.append(nums[i // 2] + nums[i // 2 + 1])
            max_val = max(max_val, nums[-1])
        
        return max_val
```

This still uses O(n) space but is slightly more efficient in practice.

# Tags

`#dynamic-programming` `#array` `#simulation` `#math`

