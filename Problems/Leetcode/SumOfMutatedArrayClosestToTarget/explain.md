## Problem

https://leetcode.com/problems/sum-of-mutated-array-closest-to-target/description/

Given an integer array `arr` and a target value `target`, return the integer `value` such that when we change all integers **larger than** `value` in the array to equal `value`, the sum of the mutated array gets as close as possible (minimum absolute difference) to `target`.

In case of a tie in absolute difference, return the **minimum** such integer. The answer is not necessarily an element of `arr`.

**Constraints:**
- `1 <= arr.length <= 10^4`
- `1 <= arr[i], target <= 10^5`

**Examples:**
- `arr = [4,9,3], target = 10` → `3` (array becomes `[3,3,3]`, sum = 9)
- `arr = [2,3,5], target = 10` → `5` (array stays `[2,3,5]`, sum = 10)
- `arr = [60864,25176,27249,21296,20204], target = 56803` → `11361`

## Observations

1. **Define a monotone function.** Let `f(v)` = sum of `min(arr[i], v)` for all `i`. As `v` increases from `0` to `max(arr)`, `f(v)` is **non-decreasing** (capping at a higher threshold can only keep or raise the sum). This means `f` is unimodal with respect to the absolute difference `|f(v) - target|`.

2. **The search space is continuous integers `[0, max(arr)]`.** Any `value > max(arr)` gives the same sum as `max(arr)`, so we can cap the right bound there.

3. **Ternary search applies.** Because `f(v)` is monotonically non-decreasing, the cost function `|f(v) - target|` is **unimodal** (it decreases then increases, or is flat then increases). Ternary search finds the minimum of a unimodal function on a discrete range in `O(log n)` iterations.

4. **Tie-breaking toward the minimum.** When two candidates produce equal absolute differences, we prefer the smaller one. This is handled by updating `best_val` only when `diff < best_diff` **or** (`diff == best_diff` and `candidate < best_val`).

5. **Each `f(v)` evaluation is O(n).** Overall complexity is `O(n log(max(arr)))`.

## Solution

We perform **ternary search** over the integer range `[0, max(arr)]`.

At each step:
- Pick two probe points `mid1 = left + (right - left) / 3` and `mid2 = right - (right - left) / 3`, splitting the range into three roughly equal thirds.
- Compute `f(mid1)` and `f(mid2)` and their absolute differences from `target`.
- Track the global best `(best_diff, best_val)` including tie-breaking.
- If `diff1 > diff2`, the minimum cannot be in `[left, mid1]`, so move `left = mid1 + 1`.
- Otherwise, the minimum cannot be in `[mid2, right]`, so move `right = mid2 - 1`.
- Repeat until the window collapses.

```python
class Solution:
    def findBestValue(self, arr: List[int], target: int) -> int:
        left = 0
        right = max(arr)

        def f_sum_threshold(threshold: int) -> int:
            # Sum of array with all values capped at `threshold`
            return sum(min(val, threshold) for val in arr)

        best_val = 0
        best_diff = float('inf')

        while left <= right:
            mid1 = left + (right - left) // 3
            mid2 = right - (right - left) // 3

            s1 = f_sum_threshold(mid1)
            s2 = f_sum_threshold(mid2)
            diff1 = abs(s1 - target)
            diff2 = abs(s2 - target)

            # Update best, preferring smaller value on tie
            if diff1 < best_diff or (diff1 == best_diff and mid1 < best_val):
                best_diff = diff1
                best_val = mid1
            if diff2 < best_diff or (diff2 == best_diff and mid2 < best_val):
                best_diff = diff2
                best_val = mid2

            # Eliminate the third that cannot contain the minimum
            if diff1 > diff2:
                left = mid1 + 1
            else:
                right = mid2 - 1

        return best_val
```

**Why ternary search works here:** `f(v)` is non-decreasing, so `|f(v) - target|` is unimodal — it either decreases to a minimum then increases, or is strictly one-sided. Ternary search eliminates one-third of the search space per iteration, giving `O(log_{3/2}(max(arr)))` iterations ≈ ~100 iterations for `max(arr) = 10^5`.

**Edge cases:**
- If `f(0) >= target` (target is already ≤ zero-sum, impossible given constraints, but `value = 0` would be checked).
- If `f(max(arr)) < target`, the best we can do is `value = max(arr)` keeping the original sum.

# Tags

`Binary Search` `Ternary Search` `Array`

