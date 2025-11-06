import heapq
from typing import List

class Solution:
    def kWeakestRows(self, mat: List[List[int]], k: int) -> List[int]:
        m = len(mat)
        n = len(mat[0])
        pq = []
        for i in range(m):
            heapq.heappush(pq, (sum(mat[i]), i))
        res = []
        while pq and k:
            s, i = heapq.heappop(pq)
            res.append(i)
            k -= 1
        return res