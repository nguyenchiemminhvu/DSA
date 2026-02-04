from typing import List
import heapq

class Solution:
    def halveArray(self, nums: List[int]) -> int:
        total = sum(nums)
        half = total / 2

        pq = []
        for val in nums:
            heapq.heappush(pq, -val)
        count = 0
        total = 0
        while total < half:
            val = -heapq.heappop(pq)
            val /= 2
            total += val
            heapq.heappush(pq, -val)
            count += 1
        return count