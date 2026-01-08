from typing import List
import heapq

class Solution:
    def kthSmallest(self, mat: List[List[int]], k: int) -> int:
        n = len(mat)
        pq = []
        for row in mat:
            for val in row:
                heapq.heappush(pq, -val)
                if len(pq) > k:
                    heapq.heappop(pq)
        
        return -heapq.heappop(pq)