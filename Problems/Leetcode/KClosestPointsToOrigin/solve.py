from typing import List
import heapq

class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        pq = []
        for x, y in points:
            heapq.heappush(pq, (-(x**2 + y**2), (x, y)))
            if len(pq) > k:
                heapq.heappop(pq)

        return [item[1] for item in pq]