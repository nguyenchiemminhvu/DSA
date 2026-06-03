from typing import List

class Solution:
    def garbageCollection(self, garbage: List[str], travel: List[int]) -> int:
        n = len(garbage)

        res = sum(len(g) for g in garbage)
        last_idx_m = last_idx_g = last_idx_p = 0
        for i in range(n):
            if 'M' in garbage[i]:
                last_idx_m = i
            if 'G' in garbage[i]:
                last_idx_g = i
            if 'P' in garbage[i]:
                last_idx_p = i

        for i in range(last_idx_m):
            res += travel[i]
        for i in range(last_idx_g):
            res += travel[i]
        for i in range(last_idx_p):
            res += travel[i]
        return res