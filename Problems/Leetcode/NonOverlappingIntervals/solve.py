from typing import List

class Solution:
    def eraseOverlapIntervals(self, intervals: List[List[int]]) -> int:
        intervals.sort(key=lambda x: (x[1], x[0]))

        removed = 0
        prev_interval = intervals[0]
        for i in range(1, len(intervals)):
            if intervals[i][0] >= prev_interval[1]:
                prev_interval = intervals[i]
            else:
                removed += 1
        return removed