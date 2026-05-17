## Problem

https://leetcode.com/problems/longest-mountain-in-array/description

An array `arr` is a mountain array if and only if:
- `arr.length >= 3`
- There exists some index `i` (0-indexed) with `0 < i < arr.length - 1` such that:
  - `arr[0] < arr[1] < ... < arr[i - 1] < arr[i]` (strictly ascending to peak)
  - `arr[i] > arr[i + 1] > ... > arr[arr.length - 1]` (strictly descending from peak)

Given an integer array `arr`, **return the length of the longest subarray which is a mountain**. Return 0 if there is no mountain subarray.

**Examples:**
- Input: `arr = [2,1,4,7,3,2,5]` → Output: `5` (mountain is `[1,4,7,3,2]`)
- Input: `arr = [2,2,2]` → Output: `0` (no strictly increasing/decreasing sequences)

**Constraints:**
- `1 <= arr.length <= 10^4`
- `0 <= arr[i] <= 10^4`

**Follow-up:** Can you solve it using only one pass? Can you solve it in O(1) space?

## Observations

1. **Mountain structure requirement**: A valid mountain must have:
   - At least 3 elements
   - A strictly ascending part (at least 1 element)
   - A peak element
   - A strictly descending part (at least 1 element)

2. **No plateaus allowed**: Equal consecutive elements break the mountain sequence because we need strict inequalities (< and >).

3. **Peak as transition point**: The peak is the element where we transition from ascending to descending. When we see a value greater than the previous after descending, we've found a new potential mountain and must reset.

4. **One-pass efficiency**: By tracking the current ascending and descending lengths as we iterate, we can find all mountains in a single pass without pre-computing anything, achieving O(1) space and O(n) time.

5. **State machine concept**: At each position, we're in one of three states:
   - Ascending phase (counting up increments)
   - Descending phase (counting down increments)
   - Reset (when constraints are violated)

## Solution

```python
class Solution:
    def longestMountain(self, arr: List[int]) -> int:
        n = len(arr)
        up = down = 0  # Track ascending and descending segment lengths
        res = 0
        
        for i in range(1, n):
            # Reset if we're ascending again after descending (new mountain starting)
            if down > 0 and arr[i] > arr[i - 1]:
                up = down = 0
            
            # Count ascending segment
            if arr[i] > arr[i - 1]:
                up += 1
            # Count descending segment
            elif arr[i] < arr[i - 1]:
                down += 1
            # Reset on plateau (equal elements break mountain structure)
            else:
                up = down = 0
            
            # Update result when we have both ascending and descending parts
            if up > 0 and down > 0:
                res = max(res, up + down + 1)
        
        return res
```

**Algorithm Walkthrough:**

For `arr = [2,1,4,7,3,2,5]`:

| i | arr[i] | Comparison | up | down | Action | res |
|---|--------|-----------|----|----|--------|-----|
| 1 | 1 | 1 < 2 | 0 | 1 | Start descending | 0 |
| 2 | 4 | 4 > 1, down > 0 | 0 | 0 | Reset (new mountain) | 0 |
| 2 | 4 | 4 > 1 | 1 | 0 | Start ascending | 0 |
| 3 | 7 | 7 > 4 | 2 | 0 | Continue ascending | 0 |
| 4 | 3 | 3 < 7 | 2 | 1 | Start descending | max(0, 2+1+1)=4 |
| 5 | 2 | 2 < 3 | 2 | 2 | Continue descending | max(4, 2+2+1)=5 |
| 6 | 5 | 5 > 2, down > 0 | 0 | 0 | Reset (new mountain) | 5 |
| 6 | 5 | 5 > 2 | 1 | 0 | Start ascending | 5 |

**Result:** 5 (subarray `[1,4,7,3,2]`)

**Key Insights:**

- **Reset condition**: `if down > 0 and arr[i] > arr[i - 1]` catches when we transition back to ascending after descending, forcing a reset of the current mountain state.
- **Plateau handling**: `else: up = down = 0` ensures equal consecutive values terminate the mountain sequence.
- **Mountain detection**: We only track the mountain when both `up > 0` and `down > 0`, meaning we've completed at least one ascending and one descending sequence.
- **Length calculation**: Total length = `up + down + 1` (the +1 accounts for the peak element).

**Complexity:**
- **Time:** O(n) - single pass through array
- **Space:** O(1) - only tracking counters and result

# Tags

