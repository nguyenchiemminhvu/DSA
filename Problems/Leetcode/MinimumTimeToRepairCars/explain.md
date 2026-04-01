## Problem

https://leetcode.com/problems/minimum-time-to-repair-cars/description/

You are given an integer array `ranks` representing the ranks of some mechanics. `ranks[i]` is the rank of the i-th mechanic. A mechanic with rank `r` can repair `n` cars in `r * n²` minutes.

You are also given an integer `cars` representing the total number of cars waiting in the garage to be repaired.

Return the minimum time taken to repair all the cars.

**Note:** All the mechanics can repair the cars simultaneously.

**Constraints:**
- `1 <= ranks.length <= 10^5`
- `1 <= ranks[i] <= 100`
- `1 <= cars <= 10^6`

## Observations

1. **Monotonic feasibility**: If all cars can be repaired within time `t`, they can also be repaired within any time `t' > t`. This monotonic property makes the problem a candidate for binary search on the answer.

2. **Cars repaired by one mechanic in time `t`**: A mechanic with rank `r` repairs `n` cars in `r * n²` minutes. Solving for `n` given a time budget `t`: `n = floor(sqrt(t / r))`. This is the maximum cars that mechanic can handle.

3. **Feasibility check**: For a fixed time `t`, sum `floor(sqrt(t / r))` over all mechanics. If the total is `>= cars`, then `t` is achievable.

4. **Search bounds**:
   - Lower bound: `1` (at least 1 minute).
   - Upper bound: `max(ranks) * cars²` — the time needed if the worst-ranked mechanic repaired all cars alone. The true answer is always within this range.

## Solution

Binary search on the answer (time `t`):

- **Search space**: `[1, max(ranks) * cars²]`
- **Condition**: `check_possible(t)` returns `True` if the total cars all mechanics can repair within `t` minutes is `>= cars`.
- **Strategy**: Find the smallest `t` for which `check_possible(t)` is `True`.

```python
from math import sqrt

class Solution:
    def repairCars(self, ranks: List[int], cars: int) -> int:
        def check_possible(t: int) -> bool:
            count = 0
            for r in ranks:
                count += int(sqrt(t // r))
            return count >= cars

        left, right = 1, max(ranks) * (cars ** 2)
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
- Time: `O(n * log(max_rank * cars²))` — binary search over the time range, each step checks all `n` mechanics.
- Space: `O(1)`

# Tags

Binary Search, Math

