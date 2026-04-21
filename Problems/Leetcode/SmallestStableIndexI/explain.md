## Problem

https://leetcode.com/problems/smallest-stable-index-i/description/

Given an integer array `nums` of length n and an integer `k`, find the smallest **stable index**.

For each index i:
- **Instability score** = max(nums[0..i]) - min(nums[i..n-1])
- An index is **stable** if instability score ≤ k

Return the smallest stable index, or -1 if none exists.

**Constraints:**
- 1 ≤ nums.length ≤ 100
- 0 ≤ nums[i] ≤ 10⁹
- 0 ≤ k ≤ 10⁹

**Examples:**
- nums = [5,0,1,4], k = 3 → Output: 3 (instability at index 3: 5-4=1 ≤ 3)
- nums = [3,2,1], k = 1 → Output: -1 (all indices have instability 2 > 1)
- nums = [0], k = 0 → Output: 0 (instability: 0-0=0 ≤ 0)

## Observations

1. **Naive approach is inefficient**: Iterating through each index and computing max/min ranges repeatedly would be O(n²), slow for repeated calculations.

2. **Key insight**: We can precompute:
   - Prefix max: max value from index 0 to i (increases or stays same as i increases)
   - Suffix min: min value from index i to n-1 (decreases or stays same as i increases)

3. **Monotonic properties**:
   - Prefix max is non-decreasing: `prefix_max[i] ≥ prefix_max[i-1]`
   - Suffix min is non-increasing: `suffix_min[i] ≤ suffix_min[i+1]`

4. **Early termination**: Once we find the first stable index, we can return immediately since we're looking for the **smallest** one. No need to check further.

5. **Array structure optimization**: Store both prefix max and suffix min in a single array `prefix[i] = [max_val, min_val]` to reduce space overhead and improve cache locality.

## Solution

```python
class Solution:
    def firstStableIndex(self, nums: list[int], k: int) -> int:
        n = len(nums)
        # prefix[i] stores [max(nums[0..i]), min(nums[i..n-1])]
        prefix = [[val, val] for val in nums]
        
        # Build prefix max array
        for i in range(1, n):
            prefix[i][0] = max(prefix[i - 1][0], prefix[i][0])
        
        # Build suffix min array (backward)
        for i in range(n - 2, -1, -1):
            prefix[i][1] = min(prefix[i + 1][1], prefix[i][1])
        
        # Find first stable index
        for i in range(n):
            instability = prefix[i][0] - prefix[i][1]
            if instability <= k:
                return i
        return -1
```

**Algorithm Breakdown:**

1. **Initialization** (Line 3-4): Create `prefix` array where each element initially holds `[nums[i], nums[i]]`

2. **Prefix Max Pass** (Lines 6-7): Build forward pass to compute max from 0 to i
   - For each position i, take the max of previous prefix max and current value
   - Time: O(n), Space: O(1) extra

3. **Suffix Min Pass** (Lines 9-10): Build backward pass to compute min from i to n-1
   - Iterate from second-to-last index backward
   - For each position i, take the min of current value and next suffix min
   - Time: O(n), Space: O(1) extra

4. **Search Loop** (Lines 12-15): Find first stable index
   - For each index, compute instability = max - min
   - Return immediately when condition is met
   - Worst case: O(n) iterations

**Time Complexity**: O(n) - three separate passes through the array
**Space Complexity**: O(n) - for the prefix array storing max/min pairs

**Example Walkthrough** (nums = [5,0,1,4], k = 3):

| i | nums[i] | prefix_max | suffix_min | instability | stable? |
|---|---------|-----------|-----------|------------|---------|
| 0 | 5 | 5 | 0 | 5 - 0 = 5 | ❌ |
| 1 | 0 | 5 | 0 | 5 - 0 = 5 | ❌ |
| 2 | 1 | 5 | 1 | 5 - 1 = 4 | ❌ |
| 3 | 4 | 5 | 4 | 5 - 4 = 1 | ✅ |

Result: 3 (first stable index found)

# Tags
- Array Prefix/Suffix Precomputation
- Single Pass Scan
- Greedy (return first valid)

