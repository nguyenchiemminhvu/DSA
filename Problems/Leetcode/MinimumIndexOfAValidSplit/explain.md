## Problem

https://leetcode.com/problems/minimum-index-of-a-valid-split/description/

An element `x` of an integer array `arr` of length `m` is **dominant** if `2 * count(x) > m` (i.e., it appears in more than half the elements).

Given a 0-indexed integer array `nums` of length `n` with **exactly one dominant element**, find the **minimum index** `i` such that splitting `nums` into `nums[0..i]` and `nums[i+1..n-1]` produces two subarrays that **both share the same dominant element** as `nums`.

Return the minimum valid split index, or `-1` if no valid split exists.

---

## Observations

1. **Dominant element is unique.**  
   Since `nums` has exactly one dominant element, we can identify it by finding the element with the highest frequency (which must exceed `n / 2`). This is the only candidate for a valid split — both subarrays must be dominant by the same element.

2. **Only one candidate to check.**  
   Because the dominant element `dval` appears more than `n/2` times in `nums`, any valid split must use `dval` as the dominant element for both halves. We never need to consider any other element.

3. **Counting prefix occurrences is sufficient.**  
   As we iterate through split point `i` (from `0` to `n-2`), we maintain:
   - `count_dval`: occurrences of `dval` in the left subarray `nums[0..i]`
   - `count_dval_right = max_count - count_dval`: occurrences of `dval` in the right subarray `nums[i+1..n-1]`

4. **Dominance condition.**  
   A split at index `i` is valid if:
   - Left subarray (`nleft = i + 1` elements): `2 * count_dval > nleft`  →  `count_dval > nleft // 2`
   - Right subarray (`nright = n - nleft` elements): `2 * count_dval_right > nright`  →  `count_dval_right > nright // 2`

5. **Return early.**  
   Since we iterate left to right, the first `i` that satisfies both conditions is automatically the minimum index.

---

## Solution Explanation

```python
class Solution:
    def minimumIndex(self, nums: List[int]) -> int:
        n = len(nums)
        counter = Counter(nums)
        max_count = 0
        dval = -1

        # Step 1: Find the dominant element and its total count
        for k, v in counter.items():
            if max_count < v:
                max_count = v
                dval = k
        
        # Step 2: Sweep through all valid split points
        count_dval = 0
        for i in range(n - 1):
            if nums[i] == dval:
                count_dval += 1       # update prefix count of dominant element

            nleft = i + 1             # size of left subarray
            nright = n - nleft        # size of right subarray
            count_dval_right = max_count - count_dval  # suffix count

            # Check dominance for both halves
            if count_dval > (nleft // 2) and count_dval_right > (nright // 2):
                return i

        return -1
```

**Step 1 — Identify the dominant element:**  
Use a frequency counter to find `dval` (the element with the highest count). Its total count is stored as `max_count`. Since the problem guarantees exactly one dominant element, this is always well-defined.

**Step 2 — Greedy left-to-right sweep:**  
For each candidate split index `i` (from `0` to `n-2`):
- Accumulate `count_dval` as we include `nums[i]` in the left half.
- Derive `count_dval_right` from `max_count - count_dval` (no second pass needed).
- Evaluate the dominance condition for both halves using integer division.
- Return `i` immediately on the first match (minimum index guarantee).

**Why `> nleft // 2` works:**  
The condition `2 * count > size` is equivalent to `count > size / 2`. For integers, `count > size // 2` holds exactly when `2 * count > size`, because if `size` is odd, `size // 2 = (size - 1) / 2`, and `count >= (size + 1) / 2` satisfies both.

**Time Complexity:** $O(n)$ — one pass to build the counter, one pass for the sweep.  
**Space Complexity:** $O(n)$ — for the frequency counter (at most $n$ distinct elements).
