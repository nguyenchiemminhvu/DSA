## Problem

https://leetcode.com/problems/minimize-maximum-of-array/description/

Given a 0-indexed array `nums` of `n` non-negative integers. In one operation, pick index `i` (1 ≤ i < n, nums[i] > 0), decrease `nums[i]` by 1, and increase `nums[i-1]` by 1. Return the minimum possible value of the maximum element after any number of operations.

## Observations

1. **Values only move left.** An element at index `i` can only give value to `i-1`, never receive from `i-1` or push rightward. There is no way to move a value to the right.

2. **`nums[0]` can only increase.** Nothing is to its left, so it can only receive value. The answer is always `≥ nums[0]`.

3. **Prefix sums are non-decreasing invariants.** The sum of any prefix `[0..k]` can only stay the same or grow (values flow in from index `k+1` but never flow out). This gives a lower bound: to fit all `k+1` elements within some maximum `m`, we need `m ≥ ⌈sum(nums[0..k]) / (k+1)⌉`.

4. **The answer is monotone.** If it is possible to make the maximum ≤ `m`, it is also possible for any `m' > m`. This makes the answer binary-searchable.

## Solution

**Binary search** on the answer `m` in the range `[nums[0], max(nums)]`.

For each candidate `m`, verify feasibility with a right-to-left sweep:

- Maintain a `carry` representing excess value that must be pushed leftward.
- For each index `i` from `n-1` down to `0`:
  - `cur = nums[i] + carry` (total value that must be placed at or to the left of `i`).
  - If `cur > m`: the overflow `cur - m` cannot stay at `i`, so it becomes the new `carry` to push left.
  - If `cur ≤ m`: index `i` can absorb everything; `carry = 0`.
- After processing index `0`, if `carry == 0` the bound is achievable; otherwise it is not (there is leftover that has nowhere to go).

**Why right-to-left?** We greedily try to keep each element as small as possible by pushing excess as far left as it needs to go, stopping as soon as it fits.

```python
class Solution:
    def minimizeArrayValue(self, nums: List[int]) -> int:
        n = len(nums)

        def check_possible(upper: int) -> bool:
            carry = 0
            for i in range(n - 1, -1, -1):
                cur = nums[i] + carry
                if cur > upper:
                    carry = cur - upper
                else:
                    carry = 0
            return carry == 0

        left = nums[0]
        right = max(nums)
        res = right
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                res = mid
                right = mid - 1
            else:
                left = mid + 1
        return res
```

**Complexity:** O(n log(max(nums))) — O(log(max)) binary search iterations, each with an O(n) check.

> **Alternative O(n) greedy:** The answer equals `max over all i of ⌈prefix_sum[i] / (i+1)⌉`, because the minimum achievable maximum for the first `i+1` elements is exactly that ceiling (the prefix sum is fixed from below and distributes as evenly as possible).

# Tags

`binary-search` `greedy` `prefix-sum`

