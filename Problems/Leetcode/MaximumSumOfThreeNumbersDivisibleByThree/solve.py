from typing import List
import heapq

class Solution:
    def maximumSum(self, nums: List[int]) -> int:
        pq = [[] for _ in range(3)]
        for val in nums:
            rem = val % 3
            heapq.heappush(pq[rem], -val)
        
        res = 0
        if len(pq[0]) >= 3:
            temp = pq[0][:]
            a, b, c = heapq.heappop(temp), heapq.heappop(temp), heapq.heappop(temp)
            res = max(res, -a - b - c)
        
        if len(pq[1]) >= 3:
            temp = pq[1][:]
            a, b, c = heapq.heappop(temp), heapq.heappop(temp), heapq.heappop(temp)
            res = max(res, -a - b - c)
        
        if len(pq[2]) >= 3:
            temp = pq[2][:]
            a, b, c = heapq.heappop(temp), heapq.heappop(temp), heapq.heappop(temp)
            res = max(res, -a - b - c)
        
        if pq[0] and pq[1] and pq[2]:
            res = max(res, (-pq[0][0] - pq[1][0] - pq[2][0]))
        
        return res