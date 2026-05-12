from typing import List

class Solution:
    def insert(self, intervals: List[List[int]], new_interval: List[int]) -> List[List[int]]:
        intervals.append(new_interval)
        prev = len(intervals) - 2
        while prev >= 0 and intervals[prev][0] > intervals[prev + 1][0]:
            intervals[prev], intervals[prev + 1] = intervals[prev + 1], intervals[prev]
            prev -= 1
        
        # here apply the same merge interval problem
        res = [intervals[0]]
        for i in range(1, len(intervals)):
            prev = res[-1]
            if intervals[i][0] <= prev[1]:
                prev[1] = max(prev[1], intervals[i][1])
            else:
                res.append(intervals[i])
        return res