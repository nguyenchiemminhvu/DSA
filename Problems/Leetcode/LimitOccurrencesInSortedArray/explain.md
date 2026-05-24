## Problem

https://leetcode.com/problems/limit-occurrences-in-sorted-array/description/

Given a **sorted** integer array `nums` and an integer `k`, return an array such that each **distinct** element appears **at most** `k` times, while preserving the relative order of elements.

**Key Constraint:** If a distinct element appears at least `k` times, it must appear **exactly** `k` times in the result.

**Examples:**

1. `nums = [1,1,1,2,2,3], k = 2` → `[1,1,2,2,3]`
   - Element 1 appears 3 times, keep only 2
   - Element 2 appears 2 times, keep both
   - Element 3 appears 1 time, keep it

2. `nums = [1,2,3], k = 1` → `[1,2,3]`
   - All elements already appear at most once

**Constraints:**
- `1 <= nums.length <= 100`
- `1 <= nums[i] <= 100`
- `nums` is sorted in non-decreasing order
- `1 <= k <= nums.length`

**Follow-up:** Can you solve this in-place with O(1) extra space?

## Observations

1. **Array is Sorted:** The sorted property is key—all occurrences of the same element are grouped consecutively.

2. **Distinct Element Detection:** Since the array is sorted, when we encounter a value different from (specifically, greater than) the previous value, we know we've moved to a new distinct element. This allows us to reset our occurrence counter.

3. **Count Management:** We only need to track:
   - The current element value being processed
   - How many times we've seen the current element
   - Whether the count has reached the limit `k`

4. **Linear Single Pass:** We can process the entire array in one pass, eliminating elements that exceed the limit.

## Solution

```python
class Solution:
    def limitOccurrences(self, nums: list[int], k: int) -> list[int]:
        current_val = -1
        current_count = 0
        res = []
        
        for val in nums:
            # New distinct element detected (because array is sorted)
            if val > current_val:
                current_val = val
                current_count = 1
            else:
                # Same element, increment count
                current_count += 1
            
            # Add to result only if we haven't exceeded k occurrences
            if current_count <= k:
                res.append(val)
        
        return res
```

**Algorithm Walkthrough:**

For `nums = [1,1,1,2,2,3], k = 2`:

| Iteration | val | val > current_val? | current_val | current_count | current_count ≤ k? | res |
|-----------|-----|-------------------|-------------|----------------|-------------------|-----|
| 0 | 1 | 1 > -1 ✓ | 1 | 1 | ✓ | [1] |
| 1 | 1 | 1 > 1 ✗ | 1 | 2 | ✓ | [1,1] |
| 2 | 1 | 1 > 1 ✗ | 1 | 3 | ✗ | [1,1] |
| 3 | 2 | 2 > 1 ✓ | 2 | 1 | ✓ | [1,1,2] |
| 4 | 2 | 2 > 2 ✗ | 2 | 2 | ✓ | [1,1,2,2] |
| 5 | 3 | 3 > 2 ✓ | 3 | 1 | ✓ | [1,1,2,2,3] |

**Complexity Analysis:**
- **Time:** O(n) — single pass through the array
- **Space:** O(1) extra space (excluding the output array) — only tracking current value and count
- **Output:** O(n) in worst case for the result array

# Tags

