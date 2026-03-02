````markdown
## Problem

https://leetcode.com/problems/subarray-product-less-than-k/description/

Given an array of integers `nums` and an integer `k`, return the number of **contiguous subarrays** where the product of all the elements in the subarray is **strictly less than** `k`.

**Example 1:**
```
Input:  nums = [10, 5, 2, 6], k = 100
Output: 8
Explanation: The 8 subarrays with product < 100 are:
  [10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]
  Note: [10,5,2] has product = 100, which is NOT strictly less than k.
```

**Example 2:**
```
Input:  nums = [1, 2, 3], k = 0
Output: 0
```

**Constraints:**
- `1 <= nums.length <= 3 * 10^4`
- `1 <= nums[i] <= 1000`
- `0 <= k <= 10^6`

## Observations

- All elements are **positive** (`nums[i] >= 1`), so the product of a subarray is always >= 1 and never decreases when we extend it to the left.
- Because of the positive-only elements, the product has a **monotonic property**: extending a window to the right can only keep or increase the product. This makes a sliding window (two-pointer) approach valid.
- If `k <= 1`, no subarray can have a product strictly less than `k` (since every element is at least 1), so the answer is immediately `0`.
- For a fixed right endpoint `right`, once we find the **smallest valid left** such that `product(nums[left..right]) < k`, every subarray ending at `right` and starting anywhere in `[left, right]` is also valid. That gives exactly `right - left + 1` new valid subarrays for each `right`.

## Solution

**Approach: Sliding Window (Two Pointers)**

Maintain a window `[left, right]` and a running product `cur_prod` of elements inside it.

1. Expand the window by moving `right` one step to the right and multiplying `cur_prod` by `nums[right]`.
2. While `cur_prod >= k`, shrink the window from the left by dividing `cur_prod` by `nums[left]` and incrementing `left`.
3. After the shrink loop, all subarrays ending at `right` and starting from any index in `[left, right]` have product `< k`. There are `right - left + 1` such subarrays — add this count to the result.

**Why `right - left + 1` counts new subarrays correctly?**

For a window `[left, right]`, the valid subarrays ending exactly at `right` are:
```
[right], [right-1, right], ..., [left, left+1, ..., right]
```
That is exactly `right - left + 1` subarrays. Since we count these only when processing `right`, there is no double-counting.

**Complexity:**
- Time: **O(n)** — each element is added and removed from the window at most once.
- Space: **O(1)** — only a few variables are used.

```python
class Solution:
    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        if k == 0 or k == 1:
            return 0
        
        res = 0
        n = len(nums)
        left = 0
        cur_prod = 1
        for right in range(n):
            cur_prod *= nums[right]          # expand window to the right
            while cur_prod >= k:             # shrink from the left until valid
                cur_prod //= nums[left]
                left += 1
            res += (right - left + 1)        # count all subarrays ending at 'right'
        return res
```

**Trace on Example 1** — `nums = [10, 5, 2, 6]`, `k = 100`:

| right | nums[right] | cur_prod (after expand) | left (after shrink) | window        | new count | res |
|-------|-------------|------------------------|---------------------|---------------|-----------|-----|
| 0     | 10          | 10                     | 0                   | [10]          | 1         | 1   |
| 1     | 5           | 50                     | 0                   | [10,5]        | 2         | 3   |
| 2     | 2           | 100 → shrink → 10      | 1                   | [5,2]         | 2         | 5   |
| 3     | 6           | 60                     | 1                   | [5,2,6]       | 3         | 8   |

Result: **8** ✓

# Tags

`sliding-window` `two-pointers` `array`
````
