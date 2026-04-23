## Problem

https://leetcode.com/problems/maximum-candies-allocated-to-k-children/description/

Given a 0-indexed integer array `candies` where `candies[i]` is the size of the i-th pile, and an integer `k` representing the number of children, allocate piles to children such that each child receives the **same** number of candies. Each child can receive candies from **only one pile**, and piles may be split into sub-piles (but not merged). Return the **maximum** number of candies each child can get.

**Constraints:**
- `1 <= candies.length <= 10^5`
- `1 <= candies[i] <= 10^7`
- `1 <= k <= 10^12`

## Observations

1. A pile of size `s` can supply `s // val` children if each child is allocated `val` candies (integer division, no merging between piles).
2. The total number of children that can be served for a given allocation `val` is `sum(candy // val for candy in candies)`.
3. This count is **monotonically non-increasing** as `val` grows: giving each child more candies can only serve fewer (or equal) children. This monotonicity is the key property that enables binary search on the answer.
4. We want the largest `val` such that the total servable children is `>= k`.
5. The search space is `[1, max(candies)]`. If total candies `< k`, no valid allocation exists and the answer is `0`.

## Solution

Binary search on the answer value `val` (candies per child):

- **Search space:** `[1, max(candies)]`.
- **Feasibility check `check_possible(val)`:** Count how many children can be served — `sum(candy // val for candy in candies)`. If this count `>= k`, then `val` candies per child is achievable.
- **Binary search logic:**
  - If `check_possible(mid)` is true, `mid` is a valid answer; record it and try larger values (`left = mid + 1`).
  - Otherwise, the allocation is too large; try smaller values (`right = mid - 1`).
- The loop terminates when `left > right`, and `res` holds the maximum feasible allocation.

```python
class Solution:
    def maximumCandies(self, candies: List[int], k: int) -> int:
        def check_possible(val: int) -> bool:
            count = 0
            for candy in candies:
                count += candy // val
            return count >= k

        left = 1
        right = max(candies)
        res = 0
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                res = mid
                left = mid + 1
            else:
                right = mid - 1
        return res
```

**Complexity:**
- Time: $O(n \log(\max(\text{candies})))$ — binary search over up to $10^7$ values, each check is $O(n)$.
- Space: $O(1)$.

# Tags

Binary Search

