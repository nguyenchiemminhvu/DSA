from collections import defaultdict
from typing import List
import heapq

class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        n = len(nums)

        res = []
        pq = []
        mp = defaultdict(int)
        for i in range(k):
            mp[nums[i]] += 1
            heapq.heappush(pq, -nums[i])
        res.append(-pq[0])

        for i in range(k, n):
            mp[nums[i]] += 1
            heapq.heappush(pq, -nums[i])
            
            left = i - k
            mp[nums[left]] -= 1

            while pq and mp[-pq[0]] <= 0:
                heapq.heappop(pq)

            if pq:
                res.append(-pq[0])
        
        return res