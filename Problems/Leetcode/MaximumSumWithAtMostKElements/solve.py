from typing import List
import heapq

class Solution:
    def maxSum(self, grid: List[List[int]], limits: List[int], k: int) -> int:
        pq = []
        for i, row in enumerate(grid):
            heapq.heapify(row)
            while len(row) > limits[i]:
                heapq.heappop(row)
            pq.extend(row)
        
        heapq.heapify(pq)
        while len(pq) > k:
            heapq.heappop(pq)
        return sum(pq)