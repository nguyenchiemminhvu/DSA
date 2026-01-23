from typing import List
import heapq

class Solution:
    def kthLargestNumber(self, nums: List[str], k: int) -> str:
        pq = [int(val) for val in nums]
        heapq.heapify(pq)
        while len(pq) > k:
            heapq.heappop(pq)
        return str(pq[0])