from typing import List
import heapq

class Solution:
    def maximumSum(self, nums: List[int]) -> int:
        res = -1
        f = {}
        for val in nums:
            tmp = val
            d = 0
            while tmp:
                d += tmp % 10
                tmp //= 10
            if d not in f:
                f[d] = []
            heapq.heappush(f[d], -val)
        
        for k, arr in f.items():
            if len(arr) < 2:
                continue
            
            a = -heapq.heappop(arr)
            b = -heapq.heappop(arr)
            res = max(res, a + b)

        return res