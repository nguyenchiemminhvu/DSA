from typing import List
import heapq

class Solution:
    def minOperations(self, pq: List[int], k: int) -> int:
        heapq.heapify(pq)
        count = 0
        while pq[0] < k:
            a = heapq.heappop(pq)
            b = heapq.heappop(pq)
            heapq.heappush(pq, min(a, b) * 2 + max(a, b))
            count += 1
        return count