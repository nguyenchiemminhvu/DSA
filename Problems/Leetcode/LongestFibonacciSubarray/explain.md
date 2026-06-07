## Problem

https://leetcode.com/problems/longest-fibonacci-subarray/description/

You are given an array of **positive** integers `nums`.

A **Fibonacci** array is a contiguous sequence whose third and subsequent terms each equal the sum of the two preceding terms.

Return the length of the longest **Fibonacci subarray** in `nums`.

**Note:** Subarrays of length 1 or 2 are always Fibonacci.

**Examples:**
- `[1, 1, 1, 1, 2, 3, 5, 1]` → `5` (`nums[2..6] = [1, 1, 2, 3, 5]`)
- `[5, 2, 7, 9, 16]` → `5` (entire array)
- `[1000000000, 1000000000, 1000000000]` → `2` (sum overflows; only length-2 sequences are guaranteed valid)

**Constraints:**
- `3 <= nums.length <= 10^5`
- `1 <= nums[i] <= 10^9`

---

## Observations

1. **Minimum length is 2.** A subarray of length 1 or 2 trivially satisfies the Fibonacci property, so the answer is at least 2.

2. **The Fibonacci property is local.** Whether index `i` extends the current Fibonacci run depends only on its two immediate predecessors: `nums[i] == nums[i-1] + nums[i-2]`.

3. **A broken run resets to 2, not 0.** When `nums[i] != nums[i-2] + nums[i-1]`, the pair `(nums[i-1], nums[i])` still forms a valid length-2 Fibonacci start. There is no need to reset to 0 or 1.

4. **Single linear pass is sufficient.** Because the condition only looks back two positions, we never need to re-examine earlier elements. This gives O(n) time and O(1) space.

5. **No overflow concern in Python.** Python integers have arbitrary precision, so `nums[i-2] + nums[i-1]` never overflows regardless of the constraint `nums[i] <= 10^9`.

---

## Solution Explanation

```python
class Solution:
    def longestSubarray(self, nums: List[int]) -> int:
        n = len(nums)

        res = 2
        cur = 2
        for i in range(2, n):
            if nums[i] == nums[i - 2] + nums[i - 1]:
                cur += 1
            else:
                cur = 2
            res = max(res, cur)
        return res
```

**Walk-through:**

- `cur` tracks the length of the Fibonacci subarray ending at the current index `i`.
- `res` tracks the global maximum seen so far.
- Both start at `2` because any two-element prefix is a valid Fibonacci subarray.

**At each index `i` (starting from 2):**
- If `nums[i] == nums[i-2] + nums[i-1]`, the current element extends the ongoing run → `cur += 1`.
- Otherwise, the run breaks. The new run starts at `(nums[i-1], nums[i])` → `cur = 2`.
- Update `res = max(res, cur)`.

**Example trace on `[1, 1, 1, 1, 2, 3, 5, 1]`:**

| i | nums[i] | nums[i-2]+nums[i-1] | cur | res |
|---|---------|----------------------|-----|-----|
| 2 | 1       | 1+1 = 2  ✗           | 2   | 2   |
| 3 | 1       | 1+1 = 2  ✗           | 2   | 2   |
| 4 | 2       | 1+1 = 2  ✓           | 3   | 3   |
| 5 | 3       | 1+2 = 3  ✓           | 4   | 4   |
| 6 | 5       | 2+3 = 5  ✓           | 5   | 5   |
| 7 | 1       | 3+5 = 8  ✗           | 2   | 5   |

Result: **5**

**Complexity:**
- Time: **O(n)** — single pass through the array.
- Space: **O(1)** — only two integer variables used.
