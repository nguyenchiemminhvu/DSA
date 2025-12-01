from typing import List
import heapq

class Solution:
    def fillCups(self, amount: List[int]) -> int:
        res = 0
        pq = []
        for val in amount:
            if val:
                heapq.heappush(pq, -val)
        while pq:
            val = heapq.heappop(pq)
            val *= -1
            if pq:
                valval = heapq.heappop(pq)
                valval *= -1
                valval -= 1
                if valval > 0:
                    heapq.heappush(pq, -valval)
            val -= 1
            if val > 0:
                heapq.heappush(pq, -val)
            res += 1
        return res