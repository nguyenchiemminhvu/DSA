## Problem

https://leetcode.com/problems/remove-covered-intervals/

```
Given an array intervals where intervals[i] = [li, ri) represent the interval
[li, ri), remove all intervals that are covered by another interval in the list.

The interval [a, b) is covered by the interval [c, d) if and only if c <= a
and b <= d.

Return the number of remaining intervals.

Example 1:
Input:  intervals = [[1,4],[3,6],[2,8]]
Output: 2
Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.

Example 2:
Input:  intervals = [[1,4],[2,3]]
Output: 1

Constraints:
- 1 <= intervals.length <= 1000
- intervals[i].length == 2
- 0 <= li < ri <= 10^5
- All the given intervals are unique.
```

## Observations

1. **Definition of "covered"**: Interval `[a, b)` is covered by `[c, d)` when
   `c <= a` AND `b <= d`. Both the left side is no wider and the right side is no
   narrower — meaning `[c, d)` fully contains `[a, b)`.

2. **Sorting unlocks a single-pass scan**: If we sort intervals by their left
   endpoint in ascending order, then for any interval we process, every previously
   seen interval already satisfies the left-coverage condition (`c <= a`). To
   determine if the current interval is covered, we only need to check whether
   some prior interval's right endpoint `d >= b`.

3. **Tie-breaking on left endpoints matters**: When two intervals share the same
   left endpoint (e.g., `[2, 5)` and `[2, 8)`), the wider interval `[2, 8)` must
   be processed first. If we don't do this, we might mistakenly count the smaller
   interval `[2, 5)` as surviving before the bigger one is recorded.
   → Sort ascending by `li`; for equal `li`, sort **descending** by `ri`.

4. **Tracking the running maximum right endpoint**: After sorting correctly, we
   only need one variable `maxRight` — the largest right endpoint seen so far
   among all intervals we decided to keep (i.e., were not covered).
   - If the current interval's right endpoint `r > maxRight`, it is NOT covered by
     any previous interval → it survives, and we update `maxRight = r`.
   - If `r <= maxRight`, a previous interval already stretches at least as far to
     the right, and since the left side is also covered by the sort order, this
     interval is completely swallowed → discard it.

5. **No nested loop needed**: Because of the sort + `maxRight` tracking, we never
   need to compare every pair of intervals. A single linear pass after the sort is
   sufficient, giving an overall O(n log n) solution.

## Solution

### Approach: Sort + Greedy Single Pass

Sort the intervals with a two-key comparator, then greedily sweep through them
while maintaining the farthest right boundary seen so far.

### Algorithm Steps:

1. **Sort** intervals: primary key = `li` ascending, secondary key = `ri` descending.
2. **Initialize** `maxRight = 0` and `count = 0`.
3. **Sweep**: for each interval `[l, r]`:
   - If `r > maxRight` → the interval is NOT covered → `count++`, `maxRight = r`.
   - Else → the interval IS covered → skip.
4. **Return** `count`.

### Why the tie-breaking sort works:

Consider `intervals = [[2, 8], [2, 5]]` after sorting (same `l`, larger `r` first):

```
Process [2, 8]: r=8 > maxRight=0 → keep, maxRight=8, count=1
Process [2, 5]: r=5 <= maxRight=8 → covered by [2,8] → skip
Result: 1 ✓
```

Without the tie-break (smaller `r` first → `[[2,5],[2,8]]`):
```
Process [2, 5]: r=5 > maxRight=0 → keep, maxRight=5, count=1
Process [2, 8]: r=8 > maxRight=5 → keep, maxRight=8, count=2  ← WRONG
```

### Example Walkthrough:

**Example 1**: `intervals = [[1,4],[3,6],[2,8]]`

After sort (by `l` asc, `r` desc): `[[1,4],[2,8],[3,6]]`

```
maxRight = 0, count = 0

[1, 4]: r=4 > maxRight=0 → keep,  maxRight=4, count=1
[2, 8]: r=8 > maxRight=4 → keep,  maxRight=8, count=2
[3, 6]: r=6 <= maxRight=8 → covered by [2,8] → skip

Result: 2 ✓
```

**Example 2**: `intervals = [[1,4],[2,3]]`

After sort: `[[1,4],[2,3]]`

```
maxRight = 0, count = 0

[1, 4]: r=4 > maxRight=0 → keep,  maxRight=4, count=1
[2, 3]: r=3 <= maxRight=4 → covered by [1,4] → skip

Result: 1 ✓
```

### Code:

```cpp
#include <vector>
#include <algorithm>
using namespace std;

int removeCoveredIntervals(vector<vector<int>>& intervals) {
    // Sort: ascending by left endpoint; for equal left, descending by right
    sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[0] != b[0] ? a[0] < b[0] : a[1] > b[1];
    });

    int maxRight = 0;
    int count = 0;
    for (const auto& interval : intervals) {
        int r = interval[1];
        if (r > maxRight) {   // not covered
            maxRight = r;
            count++;
        }
        // else: covered by a previous interval → skip
    }
    return count;
}
```

### Complexity Analysis:

- **Time Complexity**: O(n log n)
  - Sorting dominates; the single sweep is O(n).

- **Space Complexity**: O(1) extra (O(log n) for the sort stack)
  - Only `maxRight` and `count` are maintained during the sweep.

### Key Takeaways:

1. **Sort to reduce dimensionality**: Sorting by `li` guarantees the left-coverage
   condition is satisfied for free, reducing a 2D problem to a 1D scan.
2. **Tie-breaking is critical**: Equal left endpoints require descending `ri` order
   so that the covering interval is always encountered before the covered one.
3. **Single variable suffices**: Tracking only the maximum right endpoint is enough
   because we never need to "un-cover" an interval once a wider one has been seen.

# Tags

`Array` `Greedy` `Sorting` `Intervals`
