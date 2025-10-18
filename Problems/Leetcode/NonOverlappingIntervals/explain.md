## Problem

https://leetcode.com/problems/non-overlapping-intervals/description/

```
Given an array of intervals intervals where intervals[i] = [starti, endi], return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

Note that intervals which only touch at a point are non-overlapping. For example, [1, 2] and [2, 3] are non-overlapping.

Example 1:

Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.

Example 2:

Input: intervals = [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.

Example 3:

Input: intervals = [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.

Constraints:

1 <= intervals.length <= 105
intervals[i].length == 2
-5 * 104 <= starti < endi <= 5 * 104
```

## Observations

1. **Problem Goal**: We need to find the minimum number of intervals to remove to make the remaining intervals non-overlapping.

2. **Key Insight**: This is a greedy algorithm problem. To minimize removals, we should keep as many intervals as possible that don't overlap.

3. **Greedy Strategy**: 
   - Sort intervals by their end times (ascending)
   - Always keep the interval that ends earliest when there's a conflict
   - This maximizes the remaining space for future intervals

4. **Overlap Detection**: Two intervals `[a, b]` and `[c, d]` overlap if `a < d` and `c < b`. In our case, since we process in order, we only need to check if the current interval's start is less than the previous interval's end.

5. **Edge Case**: Intervals that only touch at a point (like `[1,2]` and `[2,3]`) are considered non-overlapping.

## Solution

1. **Sorting**: Sort intervals by end time first, then by start time `(x[1], x[0])`. This ensures we process intervals in order of when they finish.

2. **Greedy Selection**: 
   - Start with the first interval (which has the earliest end time)
   - For each subsequent interval:
     - If it doesn't overlap with the previous kept interval (`intervals[i][0] >= prev_interval[1]`), keep it
     - If it overlaps, remove it (increment counter) and keep the previous interval

3. **Why this works**: By always keeping the interval that ends earliest, we maximize the space available for future intervals, leading to the minimum number of removals.

**Time Complexity**: O(n log n) due to sorting
**Space Complexity**: O(1) excluding the space used by sorting

**Example Walkthrough** with `[[1,2],[2,3],[3,4],[1,3]]`:
1. After sorting by end time: `[[1,2],[1,3],[2,3],[3,4]]`
2. Keep `[1,2]` (first interval)
3. Check `[1,3]`: overlaps with `[1,2]` (1 < 2), so remove it. Count = 1
4. Check `[2,3]`: doesn't overlap with `[1,2]` (2 >= 2), so keep it
5. Check `[3,4]`: doesn't overlap with `[2,3]` (3 >= 3), so keep it
6. Result: 1 removal needed

## Tags

array, greedy