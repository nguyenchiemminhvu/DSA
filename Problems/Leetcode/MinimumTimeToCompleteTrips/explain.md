## Problem

https://leetcode.com/problems/minimum-time-to-complete-trips/description/

````markdown
## Problem

https://leetcode.com/problems/minimum-time-to-complete-trips/description/

You are given an array `time` where `time[i]` denotes the time taken by the `i`-th bus to complete **one** trip.

Each bus can make multiple trips successively — the next trip starts immediately after the current one finishes. All buses operate independently.

You are also given an integer `totalTrips`, which denotes the number of trips **all** buses should make in total. Return the **minimum time** required for all buses to complete at least `totalTrips` trips.

**Example 1:**
```
Input: time = [1,2,3], totalTrips = 5
Output: 3
Explanation:
- At t=1: trips completed = [1,0,0] → total = 1
- At t=2: trips completed = [2,1,0] → total = 3
- At t=3: trips completed = [3,1,1] → total = 5  ✓
```

**Example 2:**
```
Input: time = [2], totalTrips = 1
Output: 2
```

**Constraints:**
- `1 <= time.length <= 10^5`
- `1 <= time[i], totalTrips <= 10^7`

## Observations

1. **Monotonic feasibility:** If all buses can collectively complete `totalTrips` within duration `d`, they can also do so within any duration `d' > d`. This monotonic property makes binary search applicable.

2. **Counting trips at a given time:** At time `d`, bus `i` completes exactly `d // time[i]` trips. So the total trips completed across all buses is `sum(d // time[i] for i in range(n))`.

3. **Search space bounds:**
   - **Lower bound:** `1` — the minimum possible answer.
   - **Upper bound:** `totalTrips * min(time)` — in the worst case, only the fastest bus runs alone and needs `totalTrips` full trips.

4. **Binary search on the answer:** We binary search on time `d`, asking: *"Is it possible to complete at least `totalTrips` trips by time `d`?"* We shrink the search space until we find the minimum valid `d`.

## Solution

Binary search on the answer (time `d`):

- Define a predicate `check_possible(d)`: returns `True` if the total number of trips completed by all buses within time `d` is `≥ totalTrips`.
- Binary search for the smallest `d` where `check_possible(d)` is `True`.
- When `check_possible(mid)` is `True`, we try smaller values (`right = mid - 1`).
- When `False`, we need more time (`left = mid + 1`).
- After the loop, `left` is the minimum feasible time.

```python
class Solution:
    def minimumTime(self, time: List[int], totalTrips: int) -> int:
        n = len(time)

        def check_possible(dur: int) -> bool:
            count = 0
            for t in time:
                count += dur // t
            return count >= totalTrips

        left = 1
        right = totalTrips * min(time)
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                right = mid - 1
            else:
                left = mid + 1
        return left
```

**Complexity:**
- **Time:** $O(n \log(totalTrips \times \min(time)))$ — binary search over the range, with an $O(n)$ feasibility check at each step.
- **Space:** $O(1)$ extra space.

# Tags

`Binary Search` `Array`
````

## Observations

## Solution

# Tags

