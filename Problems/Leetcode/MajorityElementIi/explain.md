## Problem

https://leetcode.com/problems/majority-element-ii/description/

```
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

Example 1:
Input: nums = [3,2,3]
Output: [3]

Example 2:
Input: nums = [1]
Output: [1]

Example 3:
Input: nums = [1,2]
Output: [1,2]

Constraints:
1 <= nums.length <= 5 * 10^4
-10^9 <= nums[i] <= 10^9
```

## Observations

At most **2** elements can appear more than `⌊n/3⌋` times. If three elements each appeared more than `n/3` times, the total count would exceed `n`, which is impossible.

After sorting, identical elements are grouped together in contiguous blocks. If an element appears more than `k = n // 3` times, its block spans at least `k + 1` positions.

**Key insight:** In a sorted array, if `nums[i] == nums[i + k]`, then all elements from index `i` to `i + k` must be equal (since they are sorted and the endpoints match). This means the element at index `i` occupies at least `k + 1` consecutive positions — it appears more than `k = ⌊n/3⌋` times, so it qualifies.

Conversely, if an element's block is shorter than `k + 1`, there is no index `i` within that block where `nums[i] == nums[i + k]`, so it will never be added.

The skip `i += k` after a match is an optimization: once a majority element is detected at position `i`, all indices within the same block up to `i + k` would yield the same result, so we can jump ahead.

## Solution

**Step 1 — Sort:** Sort `nums` so equal elements are adjacent.

**Step 2 — Sliding window check:** Iterate with index `i`. At each position, check if `nums[i] == nums[i + k]`. If yes, `nums[i]` appears more than `k` times — add it to the result set and skip ahead by `k` to avoid redundant checks inside the same block.

**Step 3 — Return:** Convert the result set to a list.

```python
class Solution:
    def majorityElement(self, nums: List[int]) -> List[int]:
        n = len(nums)
        k = n // 3
        nums.sort()
        res = set()
        i = 0
        while i < n:
            if i + k < n and nums[i] == nums[i + k]:
                res.add(nums[i])
                i += k
            i += 1
        return list(res)
```

**Trace through Example 1:** `nums = [3,2,3]`, n=3, k=1
- Sorted: `[2,3,3]`
- i=0: `nums[0]=2`, `nums[1]=3` → 2 ≠ 3, i=1
- i=1: `nums[1]=3`, `nums[2]=3` → 3 == 3, add 3, i = 1+1+1 = 3
- Result: `[3]` ✓

**Trace through Example 3:** `nums = [1,2]`, n=2, k=0
- Sorted: `[1,2]`
- i=0: `nums[0]=1`, `nums[0]=1` → 1 == 1, add 1, i = 0+0+1 = 1
- i=1: `nums[1]=2`, `nums[1]=2` → 2 == 2, add 2, i = 1+0+1 = 2
- Result: `[1,2]` ✓

**Complexity:**
- Time: $O(n \log n)$ — dominated by sorting
- Space: $O(1)$ extra — the output set holds at most 2 elements

## Tags

array, sorting, majority vote
