## Problem

https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/description

Given a binary array `nums`, delete exactly one element from it.

Return the size of the longest non-empty subarray containing only 1's in the resulting array. Return 0 if there is no such subarray.

**Examples:**

1. `nums = [1,1,0,1]` → Output: `3`
   - Delete position 2 (the 0) → `[1,1,1]` → length 3

2. `nums = [0,1,1,1,0,1,1,0,1]` → Output: `5`
   - Delete position 4 (first 0 in the middle) → longest contiguous 1's is 5

3. `nums = [1,1,1]` → Output: `2`
   - Must delete one element → `[1,1]` → length 2

**Constraints:**
- `1 <= nums.length <= 10^5`
- `nums[i]` is 0 or 1

## Observations

1. **Key Insight**: We must delete exactly one element. This is equivalent to finding the longest subarray with **at most one 0**, then excluding that 0.

2. **Sliding Window Approach**: Use a two-pointer window that expands right and contracts left to maintain the invariant: window contains at most 1 zero.

3. **Return Value**: The answer is the window length minus 1 (since we must exclude the single 0 we found, or a 1 if all are 1's).

4. **Edge Cases**:
   - All 1's: Delete any 1 → return `n - 1`
   - Single element: Must delete it → return 0 (handled since window size - 1 = 0)
   - Multiple zeros: The window stops expanding when it encounters more than one 0

## Solution

**Algorithm: Sliding Window with 0-Count Tracking**

```python
class Solution:
    def longestSubarray(self, nums: List[int]) -> int:
        n = len(nums)
        k = 1  # Allow at most 1 zero in the window
        res = 0
        count = [0] * 2  # count[0] = zeros, count[1] = ones
        left = 0
        
        for right in range(n):
            count[nums[right]] += 1  # Expand window: add right element
            
            # Contract window while we have more than k zeros
            while count[0] > k:
                count[nums[left]] -= 1
                left += 1
            
            # Update result: window length - 1 (must delete one element)
            res = max(res, right - left)
        
        return res
```

**Step-by-Step Explanation:**

1. **Initialization**:
   - `k = 1`: We allow at most 1 zero in our window (which we'll delete)
   - `count = [0, 0]`: Track number of 0's and 1's
   - `left = 0`: Left pointer of window
   - `res = 0`: Maximum length found

2. **Expand Phase** (for each `right` index):
   - Add the element at `right` to the window
   - Increment the count for that element

3. **Contract Phase**:
   - While we have more than 1 zero in the window, shrink from left
   - Move `left` pointer right until we have exactly 1 zero or none

4. **Update Result**:
   - Record the window length as `right - left`
   - This length minus 1 is the answer (we delete one element from this window)
   - We don't explicitly subtract 1 because we're finding the max window that violates the constraint, ensuring we delete the problematic 0

**Time Complexity**: $O(n)$ - Each element is visited by `right` once and by `left` once
**Space Complexity**: $O(1)` - Only using a fixed-size count array

**Example Walkthrough** with `nums = [1,1,0,1]`:

| Step | right | nums[right] | count[0] | count[1] | Window | Window Size | Result |
|------|-------|-------------|----------|----------|--------|-------------|--------|
| 0    | 0     | 1           | 0        | 1        | [1]    | 1           | 1      |
| 1    | 1     | 1           | 0        | 2        | [1,1]  | 2           | 2      |
| 2    | 2     | 0           | 1        | 2        | [1,1,0]| 3           | 3      |
| 3    | 3     | 1           | 1        | 3        | [1,1,0,1]| 4         | 3      |

Final answer: `3` ✓

# Tags

