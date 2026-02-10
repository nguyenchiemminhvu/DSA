from typing import List
import heapq

class Solution:
    def unmarkedSumArray(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n = len(nums)
        pq = [] # (val, index)
        marked = set()
        s = sum(nums)
        res = []

        for i, val in enumerate(nums):
            heapq.heappush(pq, (val, i))
        
        for idx, k in queries:
            if idx not in marked:
                marked.add(idx)
                s -= nums[idx]
            for _ in range(k):
                while pq and pq[0][1] in marked:
                    heapq.heappop(pq)
                if pq:
                    val, i = heapq.heappop(pq)
                    marked.add(i)
                    s -= nums[i]
            res.append(s)
        
        return res