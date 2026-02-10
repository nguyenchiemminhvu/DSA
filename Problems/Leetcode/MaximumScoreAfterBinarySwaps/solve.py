from typing import List
import heapq

class Solution:
    def maximumScore(self, nums: List[int], s: str) -> int:
        n = len(s)
        total_1 = s.count('1')
        if total_1 == 0:
            return 0
        
        res = 0
        pq = []
        for i, ch in enumerate(s):
            heapq.heappush(pq, -nums[i])
            if ch == '1':
                res += -heapq.heappop(pq)
        return res