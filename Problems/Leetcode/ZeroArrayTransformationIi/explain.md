## Problem

https://leetcode.com/problems/zero-array-transformation-ii/description/

Given an integer array `nums` of length `n` and a 2D array `queries` where `queries[i] = [li, ri, vali]`:

- Each query allows you to decrement values at indices in the range `[li, ri]` by **at most** `vali` each (independently per index).
- Return the **minimum** `k` such that after applying the first `k` queries in order, `nums` becomes a **Zero Array** (all elements equal 0). Return `-1` if impossible.

**Example 1:**
- `nums = [2,0,2]`, `queries = [[0,2,1],[0,2,1],[1,1,3]]`
- After query 0: `[1,0,1]`. After query 1: `[0,0,0]`. Output: `2`

**Example 2:**
- `nums = [4,3,2,1]`, `queries = [[1,3,2],[0,2,1]]`
- Even after all queries: `[3,0,0,0]` — can't zero out. Output: `-1`

**Constraints:**
- `1 <= nums.length <= 10^5`, `0 <= nums[i] <= 5*10^5`
- `1 <= queries.length <= 10^5`, `1 <= vali <= 5`

## Observations

1. **Monotonicity:** If it is possible to zero out `nums` using the first `k` queries, then it is also possible using the first `k+1` queries (more capacity can only help). This monotonic property means binary search on `k` is valid.

2. **Check feasibility for a fixed k:** Given the first `k` queries, for each index `i`, the total "capacity" available is the sum of `val` values from queries whose range covers index `i`. If this capacity is `>= nums[i]` for every `i`, then we can zero out `nums`.

3. **Efficient range capacity aggregation — Difference Array:** Instead of iterating over every index for every query (O(n*k)), use a difference array to apply all `k` range increments in O(k) time and compute prefix sums in O(n) to get per-index capacity. This makes each feasibility check O(n + k).

4. **Binary search bounds:** The answer `k` lies in `[0, m]` where `m = len(queries)`. `k = 0` means no queries are applied — only valid if `nums` is already all zeros. If even all `m` queries can't produce a Zero Array, return `-1`.

## Solution

**Strategy:** Binary search on `k` + difference array to check feasibility.

**`check_possible(k)`:**
1. Build a difference array `temp` of size `n+1`.
2. For each of the first `k` queries `[l, r, val]`: `temp[l] += val`, `temp[r+1] -= val`.
3. Take prefix sums of `temp` — now `temp[i]` is the total available decrement capacity at index `i`.
4. Return `True` if `temp[i] >= nums[i]` for all `i`.

**Binary search:**
- Search in `[0, m]` for the smallest `k` where `check_possible(k)` is `True`.
- If no valid `k` found, return `-1`.

```python
class Solution:
    def minZeroArray(self, nums: List[int], queries: List[List[int]]) -> int:
        n = len(nums)
        m = len(queries)

        def check_possible(k: int) -> bool:
            temp = [0] * (n + 1)
            for i in range(k):
                l, r, val = queries[i]
                temp[l] += val
                temp[r+1] -= val
            for i in range(1, n + 1):
                temp[i] += temp[i - 1]
            return all(temp[i] >= nums[i] for i in range(n))

        left = 0
        right = m
        k = float('inf')
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                k = mid
                right = mid - 1
            else:
                left = mid + 1
        return -1 if k == float('inf') else k
```

**Complexity:**
- Each `check_possible(k)` call: O(n + k) = O(n + m)
- Binary search: O(log m) iterations
- **Total: O((n + m) log m)**

# Tags

- Binary Search
- Difference Array
- Prefix Sum
- Greedy

