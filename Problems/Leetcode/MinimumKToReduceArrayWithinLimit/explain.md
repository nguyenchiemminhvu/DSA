## Problem

https://leetcode.com/problems/minimum-k-to-reduce-array-within-limit/

Given a positive integer array `nums`, define `nonPositive(nums, k)` as the minimum number of operations to make every element of `nums` non-positive, where each operation reduces some `nums[i]` by `k`.

Return the minimum value of `k` such that `nonPositive(nums, k) <= k²`.

**Example 1:**
- Input: `nums = [3, 7, 5]`, Output: `3`
- When `k = 3`: operations = ceil(3/3) + ceil(7/3) + ceil(5/3) = 1 + 3 + 2 = 6 ≤ 3² = 9 ✓

**Example 2:**
- Input: `nums = [1]`, Output: `1`
- When `k = 1`: operations = ceil(1/1) = 1 ≤ 1² = 1 ✓

**Constraints:**
- `1 <= nums.length <= 10⁵`
- `1 <= nums[i] <= 10⁵`

## Observations

1. **Cost formula**: To make a single element `v` non-positive using step `k`, the minimum operations needed is `ceil(v / k)`. So `nonPositive(nums, k) = sum(ceil(v / k) for v in nums)`.

2. **Monotonicity**: As `k` increases, `ceil(v / k)` decreases (or stays the same) for each element, so `nonPositive(nums, k)` is **non-increasing** in `k`. Meanwhile `k²` is strictly increasing. Therefore, once a `k` satisfies the condition, all larger `k` also satisfy it — the feasibility function is monotone. This means **binary search** applies.

3. **Search space**: The smallest meaningful `k` is `1`. The largest we'd ever need is `max(nums)` (one operation per element, total ops = `n`, budget = `max(nums)²`), but bounding at `10⁵` covers the constraint limits safely.

4. **Ceiling division trick**: `ceil(v / k)` is computed as `(v + k - 1) // k` using integer arithmetic, avoiding floating point.

## Solution

Binary search on the answer `k` in the range `[1, 10⁵]`.

For a given candidate `k`, compute the total operations as:
```
ops = sum(ceil(nums[i] / k)) for all i
    = sum((nums[i] + k - 1) // k)
```
If `ops <= k²`, then `k` is feasible — search left for a smaller answer. Otherwise, search right.

**Time complexity**: O(n · log(max_val))
- Binary search runs O(log 10⁵) ≈ 17 iterations.
- Each `check_possible` call is O(n).

**Space complexity**: O(1) extra.

```python
class Solution:
    def minimumK(self, nums: List[int]) -> int:
        n = len(nums)

        def check_possible(k: int) -> bool:
            op = 0
            for val in nums:
                op += (val + k - 1) // k
            return op <= k ** 2

        low = 1
        high = 10**5
        k = high
        while low <= high:
            mid = low + (high - low) // 2
            if check_possible(mid):
                k = mid
                high = mid - 1
            else:
                low = mid + 1
        
        return k
```

# Tags

Binary Search, Math, Greedy

