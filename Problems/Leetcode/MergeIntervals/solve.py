from typing import List

class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        intervals.sort(key=lambda x: (x[0], x[1]))
        res = [intervals[0]]
        for i in range(1, len(intervals)):
            prev = res[-1]
            if intervals[i][0] <= prev[1]:
                prev[1] = max(prev[1], intervals[i][1])
            else:
                res.append(intervals[i])
        return res