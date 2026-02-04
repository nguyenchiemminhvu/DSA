from typing import List
import heapq

class Solution:
    def findScore(self, nums: List[int]) -> int:
        res = 0
        pq = []
        for i, val in enumerate(nums):
            heapq.heappush(pq, (val, i))

        marked = set()
        while pq:
            val, i = heapq.heappop(pq)
            if i not in marked:
                res += val
                marked.add(i)
                marked.add(i - 1)
                marked.add(i + 1)
        return res