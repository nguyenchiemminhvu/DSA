from typing import List
import heapq

class Solution:
    def miceAndCheese(self, nums1: List[int], nums2: List[int], k: int) -> int:
        pq = []
        for i, (val1, val2) in enumerate(zip(nums1, nums2)):
            heapq.heappush(pq, (-(val1 - val2), i))
        
        res = 0
        while pq and k > 0:
            _, i = heapq.heappop(pq)
            res += nums1[i]
            k -= 1
        
        while pq:
            _, i = heapq.heappop(pq)
            res += nums2[i]
        
        return res