## Problem

https://leetcode.com/problems/arithmetic-slices/description

An integer array is called **arithmetic** if it consists of at least three elements and if the difference between any two consecutive elements is the same.

Given an integer array `nums`, return the number of arithmetic **subarrays** of `nums`. A subarray is a contiguous subsequence of the array.

**Examples:**

```
Input: nums = [1,2,3,4]
Output: 3
Explanation: [1,2,3], [2,3,4], [1,2,3,4]

Input: nums = [1]
Output: 0
```

**Constraints:**
- `1 <= nums.length <= 5000`
- `-1000 <= nums[i] <= 1000`

## Observations

1. **Subarray vs subsequence:** We only care about *contiguous* slices, so a sliding window or nested loop over start/end indices covers all cases.

2. **Fixing the start, extending the end:** For every starting index `i`, compute `diff = nums[i+1] - nums[i]`. Then walk `j` from `i+2` forward. As long as `nums[j] - nums[j-1] == diff`, the subarray `nums[i..j]` is arithmetic — increment the counter and keep extending. The moment the difference breaks, stop (no point continuing further since the slice is no longer arithmetic).

3. **Counting correctly:** When the window `[i..j]` is arithmetic (length = `j - i + 1 >= 3`), each new valid `j` adds exactly **one** new arithmetic slice (the one ending at `j` starting at `i`). So `count += 1` per valid extension is correct.

4. **Complexity:**
   - Time: $O(n^2)$ — for each of the $n$ starting positions we scan at most $n$ elements forward.
   - Space: $O(1)$ — only a handful of variables.

5. **Edge cases:** Arrays of length 1 or 2 trivially return 0 because the outer loop `range(n - 2)` never executes.

## Solution

The approach is a **brute-force two-pointer scan** (nested loops) that is efficient enough given the constraint $n \le 5000$ ($5000^2 / 2 \approx 12.5 \times 10^6$ operations).

```python
from typing import List

class Solution:
    def numberOfArithmeticSlices(self, nums: List[int]) -> int:
        n = len(nums)

        count = 0
        for i in range(n - 2):          # fix the start of the slice
            diff = nums[i + 1] - nums[i]  # required common difference
            for j in range(i + 2, n):   # extend the end of the slice
                if nums[j] - nums[j - 1] != diff:
                    break               # arithmetic property broken — stop extending
                count += 1              # nums[i..j] is a valid arithmetic slice
        return count
```

**Walkthrough with `nums = [1, 2, 3, 4]`:**

| `i` | `diff` | `j` | slice      | valid? | count |
|-----|--------|-----|------------|--------|-------|
| 0   | 1      | 2   | [1, 2, 3]  | ✓      | 1     |
| 0   | 1      | 3   | [1, 2, 3, 4] | ✓    | 2     |
| 1   | 1      | 3   | [2, 3, 4]  | ✓      | 3     |
| 2   | 1      | —   | (loop ends)| —      | 3     |

**Result: 3** ✓

> **Alternative O(n) DP approach:** Keep a running variable `dp` = number of arithmetic slices ending at the current index. When `nums[i] - nums[i-1] == nums[i-1] - nums[i-2]`, `dp += 1`; otherwise `dp = 0`. Accumulate `count += dp`. This is optimal but the $O(n^2)$ solution is perfectly fine here.

# Tags

`Array` `Dynamic Programming` `Sliding Window`

