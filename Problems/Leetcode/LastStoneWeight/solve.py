from typing import List
import heapq

class Solution:
    def lastStoneWeight(self, stones: List[int]) -> int:
        pq = []
        for val in stones:
            heapq.heappush(pq, -val)
        
        while pq:
            val = heapq.heappop(pq)
            val *= -1
            if not pq:
                return val
            valval = heapq.heappop(pq)
            valval *= -1
            heapq.heappush(pq, -abs(val - valval))
        
        return 0