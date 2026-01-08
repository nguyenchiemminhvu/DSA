from typing import List
import heapq

class Solution:
    def minStoneSum(self, piles: List[int], k: int) -> int:
        pq = []
        for val in piles:
            heapq.heappush(pq, -val)
        
        while pq and k:
            val = heapq.heappop(pq)
            val *= -1
            removed = val >> 1
            heapq.heappush(pq, -(val - removed))
            k -= 1
        
        return -sum(pq)