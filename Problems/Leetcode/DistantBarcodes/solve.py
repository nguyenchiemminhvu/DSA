from typing import List
from collections import Counter
import heapq

class Solution:
    def rearrangeBarcodes(self, nums: List[int]) -> List[int]:
        counter = Counter(nums)
        pq = []
        for k, v in counter.items():
            heapq.heappush(pq, (-v, k))
        
        res = []
        while pq:
            v, k = heapq.heappop(pq)
            v = -v
            res.append(k)
            v -= 1
            
            if pq:
                vv, kk = heapq.heappop(pq)
                vv = -vv
                res.append(kk)
                vv -= 1
                if vv > 0:
                    heapq.heappush(pq, (-vv, kk))
            if v > 0:
                heapq.heappush(pq, (-v, k))
        
        return res