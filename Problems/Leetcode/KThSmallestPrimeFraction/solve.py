from typing import List
import heapq

class Solution:
    def kthSmallestPrimeFraction(self, arr: List[int], k: int) -> List[int]:
        n = len(arr)
        pq = []
        for i in range(n):
            for j in range(i + 1, n):
                heapq.heappush(pq, (-arr[i] / arr[j], (i, j)))
                if len(pq) > k:
                    heapq.heappop(pq)
        
        _, (iup, idown) = heapq.heappop(pq)
        return [arr[iup], arr[idown]]