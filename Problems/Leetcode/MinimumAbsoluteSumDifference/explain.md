## Problem

https://leetcode.com/problems/minimum-absolute-sum-difference/description/

Given two arrays `nums1` and `nums2` of length `n`, the **absolute sum difference** is `sum(|nums1[i] - nums2[i]|)` for all `i`. You may replace **at most one** element of `nums1` with any other element already in `nums1`. Return the minimum absolute sum difference modulo `10^9 + 7`.

## Observations

1. **Baseline total**: Compute `total = sum(|nums1[i] - nums2[i]|)` for all positions. Any replacement changes exactly one term in this sum.

2. **Effect of a replacement**: If we replace `nums1[i]` with some `nums1[j]`, the total changes by:
   `delta = |nums1[j] - nums2[i]| - |nums1[i] - nums2[i]|`
   We want `delta` to be as negative as possible, i.e. we want to **maximize the reduction**:
   `reduction = |nums1[i] - nums2[i]| - |nums1[j] - nums2[i]|`

3. **Best replacement for position `i`**: Since we want to minimize `|nums1[j] - nums2[i]|`, we need the element in `nums1` **closest** to `nums2[i]`. The identity of `j` doesn't matter — only its value.

4. **Efficient nearest-neighbor lookup**: Sort `nums1` into an auxiliary array `opts`. For each `nums2[i]`, binary search finds the insertion point (first element > `nums2[i]`). The closest element is either that element or the one immediately before it.

5. **Greedy single pick**: We compute the maximum reduction across all positions and subtract it from the total. Only one replacement is allowed, so we keep track of the single best.

6. **No reduction needed when equal**: If `nums1[i] == nums2[i]`, the diff is already `0`; no replacement can improve that position. The algorithm handles this naturally since `reduction = 0 - 0 = 0`.

## Solution

```python
class Solution:
    def minAbsoluteSumDiff(self, nums1: List[int], nums2: List[int]) -> int:
        MOD = 10**9 + 7
        n = len(nums1)

        opts = sorted(nums1)          # sorted copy for binary search

        def upper_bound(arr, target):
            # Returns index of first element strictly greater than target
            left, right = 0, len(arr) - 1
            idx = len(arr)
            while left <= right:
                mid = (left + right) // 2
                if arr[mid] > target:
                    idx = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return idx

        reduced = 0   # best (maximum) reduction found so far
        total = 0     # baseline sum of absolute differences

        for i in range(n):
            diff = abs(nums1[i] - nums2[i])
            total += diff

            # Find the nearest value in opts to nums2[i]
            upper = upper_bound(opts, nums2[i])
            best = diff                                         # worst case: keep current diff

            if upper < n:                                       # candidate just above nums2[i]
                best = min(best, abs(opts[upper] - nums2[i]))

            if upper > 0:                                       # candidate just below nums2[i]
                best = min(best, abs(opts[upper - 1] - nums2[i]))

            # How much can we reduce the total by replacing nums1[i]?
            reduced = max(reduced, diff - best)

        return (total - reduced) % MOD
```

**Why `upper_bound` checks two candidates:**  
`opts[upper]` is the smallest value in `nums1` that is **strictly greater** than `nums2[i]`, and `opts[upper - 1]` is the largest value **≤ nums2[i]`. The closest element to `nums2[i]` must be one of these two neighbours.

**Complexity:** O(n log n) — sorting once, then one binary search per element.

# Tags

`Binary Search` `Sorting` `Array` `Greedy`

