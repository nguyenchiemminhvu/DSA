from typing import List
import heapq
import math

class Solution:
    def pickGifts(self, gifts: List[int], k: int) -> int:
        pq = []
        for val in gifts:
            heapq.heappush(pq, -val)
        
        while pq and k:
            val = heapq.heappop(pq)
            val *= -1
            remain = math.floor(math.sqrt(val))
            heapq.heappush(pq, -remain)
            k -= 1

        return sum(-val for val in pq)