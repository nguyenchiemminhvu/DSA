from typing import List
import heapq

class Solution:
    def maxPoints(self, tech1: List[int], tech2: List[int], k: int) -> int:
        n = len(tech1)

        res = sum(tech1)
        pq = []
        for i in range(n):
            heapq.heappush(pq, -(tech2[i] - tech1[i]))
        
        while k < n:
            val = heapq.heappop(pq)
            val *= -1
            if val > 0:
                res += val
            k += 1

        return res