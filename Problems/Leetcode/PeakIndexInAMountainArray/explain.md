## Problem

https://leetcode.com/problems/peak-index-in-a-mountain-array/description/

You are given an integer mountain array `arr` of length `n` where the values increase to a peak element and then decrease.

Return the index of the peak element.

Your task is to solve it in **O(log(n))** time complexity.

**Constraints:**
- `3 <= arr.length <= 10^5`
- `0 <= arr[i] <= 10^6`
- `arr` is guaranteed to be a mountain array.

## Observations

- A **mountain array** strictly increases up to a peak, then strictly decreases. The peak is never at index `0` or `n-1`.
- At any index `mid`, there are three possible local shapes:
  - `arr[mid - 1] < arr[mid] > arr[mid + 1]` → `mid` is the **peak**.
  - `arr[mid - 1] < arr[mid] < arr[mid + 1]` → we are on the **ascending slope**; the peak lies to the **right**.
  - `arr[mid - 1] > arr[mid]` → we are on the **descending slope**; the peak lies to the **left**.
- This monotonic structure allows us to apply **binary search** and discard half the search space at every step, achieving O(log n).
- The search range starts at `left = 1` and `right = n - 2` because the peak can never be at the first or last index.

## Solution

```python
class Solution:
    def peakIndexInMountainArray(self, arr: List[int]) -> int:
        n = len(arr)
        left = 1
        right = n - 2

        while left <= right:
            mid = left + (right - left) // 2
            if arr[mid] > arr[mid - 1] and arr[mid] > arr[mid + 1]:
                return mid
            if arr[mid] > arr[mid - 1] and arr[mid] < arr[mid + 1]:
                left = mid + 1
            else:
                right = mid - 1
        return -1
```

**Step-by-step explanation:**

1. Initialize `left = 1`, `right = n - 2` to exclude the guaranteed non-peak boundaries.
2. Compute `mid = left + (right - left) // 2` to avoid integer overflow.
3. **Peak found:** if `arr[mid] > arr[mid-1]` and `arr[mid] > arr[mid+1]`, return `mid`.
4. **Ascending slope:** if `arr[mid] > arr[mid-1]` and `arr[mid] < arr[mid+1]`, the peak is to the right → `left = mid + 1`.
5. **Descending slope:** otherwise (`arr[mid] < arr[mid-1]`), the peak is to the left → `right = mid - 1`.
6. The loop always terminates because `arr` is guaranteed to be a mountain array, so a peak always exists.

**Complexity:**
- Time: **O(log n)** — search space halves at every iteration.
- Space: **O(1)** — only a constant number of variables used.

# Tags

`Binary Search` `Array`

