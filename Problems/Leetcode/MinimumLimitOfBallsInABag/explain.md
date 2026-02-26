## Problem

https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/description/

```
You are given an integer array nums where the ith bag contains nums[i] balls. You are also given an integer maxOperations.

You can perform the following operation at most maxOperations times:
  Take any bag of balls and divide it into two new bags with a positive number of balls.

Your penalty is the maximum number of balls in a bag. You want to minimize your penalty after the operations.
Return the minimum possible penalty after performing the operations.

Constraints:
  1 <= nums.length <= 10^5
  1 <= maxOperations, nums[i] <= 10^9
```

## Observations

- The answer (penalty) lies in the range `[1, max(nums)]`.
- The feasibility of a candidate penalty `cap` is **monotone**: if `cap` is achievable, then any larger value is also achievable. This makes binary search applicable.
- For a single bag of `val` balls to hold at most `cap` balls per sub-bag, we need `ceil(val / cap)` bags total, which costs `ceil(val / cap) - 1` split operations.
- Total operations needed for a given `cap` = `sum(ceil(nums[i] / cap)) - n`, where `n` is the original number of bags (each split adds exactly one bag).
- If this total ≤ `maxOperations`, then `cap` is a valid penalty.

## Solution

Binary search on the answer `cap` (the penalty/max balls per bag):

1. Search space: `left = 1`, `right = max(nums)`.
2. For each `mid`, call `check_possible(mid)` to count the total number of split operations required if every bag is capped at `mid` balls.
3. `check_possible(cap)`:
   - For each bag of size `val`, it requires `ceil(val / cap)` sub-bags → `ceil(val / cap) - 1` operations.
   - Total new bags = `num_bags`; operations needed = `num_bags - n`.
   - `ceil(val / cap)` is computed as `(val + cap - 1) // cap` (integer ceiling division).
4. If `check_possible(mid)` is `True`, record `mid` as a candidate and search left (`right = mid - 1`).
5. Otherwise search right (`left = mid + 1`).

```python
class Solution:
    def minimumSize(self, nums: List[int], max_op: int) -> int:
        n = len(nums)
        s = sum(nums)

        def check_possible(cap: int) -> bool:
            num_bags = 0
            for val in nums:
                if val <= cap:
                    num_bags += 1
                else:
                    num_bags += (val + cap - 1) // cap  # ceil(val / cap)
            return num_bags - n <= max_op

        left = 1
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

**Complexity:**
- Time: `O(n log(max(nums)))` — binary search over `[1, max(nums)]`, each step scans all `n` bags.
- Space: `O(1)` extra.

# Tags
#binary-search

