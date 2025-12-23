from typing import List

class Solution:
    def maxTwoEvents(self, events: List[List[int]]) -> int:
        times = []
        for e in events:
            times.append([e[0], 1, e[2]])
            times.append([e[1] + 1, 0, e[2]])
        times.sort()

        res, cur_max = 0, 0
        for t in times:
            if t[1] == 1:
                res = max(res, t[2] + cur_max)
            else:
                cur_max = max(cur_max, t[2])
        return res