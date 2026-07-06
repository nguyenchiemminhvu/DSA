from typing import List

class Solution:
    def removeCoveredIntervals(self, intervals: List[List[int]]) -> int:
        intervals.sort(key=lambda x: (x[0], -x[1]))
        n = len(intervals)
        prev = intervals[0]
        for left, right in intervals[1:]:
            if prev[0] <= left and prev[1] >= right:
                n -= 1
            else:
                prev = [left, right]
        return n