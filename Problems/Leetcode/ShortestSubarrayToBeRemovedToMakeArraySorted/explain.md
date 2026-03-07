## Problem

https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/solutions/7631942/python-solution-by-ncmv-yldh/

Given an integer array `arr`, remove a **contiguous subarray** (can be empty) such that the remaining elements are **non-decreasing**. Return the length of the shortest such subarray.

**Examples:**
- `[1,2,3,10,4,2,3,5]` → remove `[10,4,2]` (length 3), leaving `[1,2,3,3,5]`
- `[5,4,3,2,1]` → remove `[5,4,3,2]` or `[4,3,2,1]` (length 4)
- `[1,2,3]` → already sorted, remove `[]` (length 0)

**Constraints:** `1 <= arr.length <= 10^5`, `0 <= arr[i] <= 10^9`

## Observations

1. **The kept elements must form a non-decreasing sequence, and they must be a prefix + suffix of the array** — because the removed part is contiguous, whatever remains consists of a (possibly empty) prefix and a (possibly empty) suffix that are joined together.

2. **Find the longest non-decreasing prefix and suffix first:**
   - Let `left` be the last index of the longest non-decreasing prefix (i.e., `arr[0..left]` is non-decreasing).
   - Let `right` be the first index of the longest non-decreasing suffix (i.e., `arr[right..n-1]` is non-decreasing).
   - If the whole array is already sorted (`left == n-1`), return 0.

3. **Two baseline options:**
   - Remove everything after the prefix: remove `arr[left+1..n-1]`, cost = `n - left - 1`.
   - Remove everything before the suffix: remove `arr[0..right-1]`, cost = `right`.
   - The answer is at most `min(n - left - 1, right)`.

4. **Two-pointer merge to find the optimal split:**
   - We want to keep some prefix `arr[0..i]` and some suffix `arr[j..n-1]` where `arr[i] <= arr[j]` (so the junction is non-decreasing).
   - Iterate `i` from `0` to `left`, and for each `i` advance `j` (starting from `right`) until `arr[j] >= arr[i]`.
   - The cost of this split is `j - i - 1` (the middle chunk removed).
   - Track the minimum across all valid `(i, j)` pairs.

## Solution

```python
class Solution:
    def findLengthOfShortestSubarray(self, arr: List[int]) -> int:
        n = len(arr)

        # Step 1: find end of longest non-decreasing prefix
        left = 1
        while left < n and arr[left] >= arr[left - 1]:
            left += 1

        # Whole array is already sorted
        if left >= n:
            return 0

        # Step 2: find start of longest non-decreasing suffix
        right = n - 2
        while right >= 0 and arr[right] <= arr[right + 1]:
            right -= 1

        # Adjust to inclusive indices
        left -= 1   # arr[0..left] is the non-decreasing prefix
        right += 1  # arr[right..n-1] is the non-decreasing suffix

        # Step 3: baseline — remove only one side
        res = min(n - left - 1, right)

        # Step 4: two-pointer to find the best prefix[0..i] + suffix[j..n-1]
        i = 0
        j = right
        while i <= left and j < n:
            if arr[i] <= arr[j]:
                res = min(res, j - i - 1)  # remove arr[i+1..j-1]
                i += 1
            else:
                j += 1

        return res
```

**Complexity:** Time O(n), Space O(1).

**Key insight:** After locking in the non-decreasing prefix and suffix, the problem reduces to a two-pointer scan. We advance `i` when the junction condition `arr[i] <= arr[j]` holds (shrinking the removed middle), and advance `j` otherwise (looking for a larger suffix start that satisfies the condition).

# Tags

`two-pointers` `array` `medium`

