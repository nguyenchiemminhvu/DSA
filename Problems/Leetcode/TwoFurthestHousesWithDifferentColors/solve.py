from typing import List

class Solution:
    def maxDistance(self, colors: List[int]) -> int:
        d = {}
        for i, color in enumerate(colors):
            if color not in d:
                d[color] = [i]
            else:
                d[color].append(i)
        
        l = []
        for k in d.keys():
            l.append(d[k])

        res = 0
        for i in range(0, len(l)):
            for j in range(i + 1, len(l)):
                res = max([
                    res,
                    abs(l[i][0] - l[j][0]),
                    abs(l[i][0] - l[j][-1]), 
                    abs(l[i][-1] - l[j][0]),
                    abs(l[i][-1] - l[j][-1])
                ])
        return res