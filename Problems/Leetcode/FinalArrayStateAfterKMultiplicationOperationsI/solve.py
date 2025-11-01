from typing import List
import heapq

class Solution:
    def getFinalState(self, nums: List[int], k: int, multiplier: int) -> List[int]:
        pq = []
        for i, val in enumerate(nums):
            heapq.heappush(pq, (val, i))
        
        while k:
            val, i = heapq.heappop(pq)
            val *= multiplier
            heapq.heappush(pq, (val, i))
            k -= 1
        
        while pq:
            val, i = heapq.heappop(pq)
            nums[i] = val
        
        return nums