from typing import List

class Solution:
    def minCosts(self, cost: List[int]) -> List[int]:
        res = []
        cur_min = cost[0]
        for val in cost:
            cur_min = min(cur_min, val)
            res.append(cur_min)
        return res