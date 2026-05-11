## Problem

https://leetcode.com/problems/concatenate-array-with-reverse/description/

Given an integer array `nums` of length `n`, construct a new array `ans` of length `2 * n` such that:
- The first `n` elements are the same as `nums`.
- The next `n` elements are the elements of `nums` in **reverse order**.

Formally:
- `ans[i] = nums[i]` for `0 <= i <= n - 1`
- `ans[i + n] = nums[n - i - 1]` for `0 <= i <= n - 1`

**Example 1:**
```
Input:  nums = [1, 2, 3]
Output: [1, 2, 3, 3, 2, 1]
```

**Example 2:**
```
Input:  nums = [1]
Output: [1, 1]
```

**Constraints:**
- `1 <= nums.length <= 100`
- `1 <= nums[i] <= 100`

## Observations

- The output array is always exactly twice the length of the input.
- The second half is simply a mirror of the first half — the input array reversed.
- Python's slice `nums[::-1]` produces a reversed copy of `nums` in O(n) time and space.
- Using `list.extend()` appends all elements of an iterable to the end of the list in-place, which is more efficient than concatenation (`+`) since it avoids creating a third intermediate list.
- Because we slice first (`nums[::-1]` captures the original state), extending `nums` in-place is safe — the reversed copy is already computed before mutation begins.
- Edge case: a single-element array always results in `[x, x]`, which the solution handles naturally.

## Solution

```python
class Solution:
    def concatWithReverse(self, nums: list[int]) -> list[int]:
        nums.extend(nums[::-1])
        return nums
```

**Step-by-step walkthrough** (using `nums = [1, 2, 3]`):

1. `nums[::-1]` creates a reversed copy → `[3, 2, 1]`. This is evaluated **before** `extend` mutates `nums`.
2. `nums.extend([3, 2, 1])` appends each element to `nums` in order → `[1, 2, 3, 3, 2, 1]`.
3. The modified `nums` is returned.

**Complexity:**
| | |
|---|---|
| Time  | O(n) — one pass to reverse, one pass to extend |
| Space | O(n) — the reversed slice is a temporary copy of size n |

# Tags

`Array` `Simulation`
