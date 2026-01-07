from typing import List
import heapq
from collections import defaultdict

class Solution:
    def maximumImportance(self, n: int, roads: List[List[int]]) -> int:
        f = defaultdict(int)
        for a, b in roads:
            f[a] += 1
            f[b] += 1
        
        pq = []
        for k, v in f.items():
            heapq.heappush(pq, (-v, k))

        importance = n
        f_imp = {}
        while pq:
            _, city = heapq.heappop(pq)
            f_imp[city] = importance
            importance -= 1
        
        res = 0
        for a, b in roads:
            res += (f_imp[a] + f_imp[b])
        return res