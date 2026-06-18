from collections import defaultdict
from typing import List

class Solution:
    def findChampion(self, n: int, edges: List[List[int]]) -> int:
        mp = defaultdict(int)
        for u, v in edges:
            mp[v] += 1
        
        cand = -1
        for i in range(n):
            if mp[i] == 0:
                if cand != -1:
                    return -1
                cand = i
        
        return cand