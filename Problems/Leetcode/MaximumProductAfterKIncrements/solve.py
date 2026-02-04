from typing import List
import heapq

class Solution:
    def maximumProduct(self, nums: List[int], k: int) -> int:
        heapq.heapify(nums)
        for _ in range(k):
            val = heapq.heappop(nums)
            heapq.heappush(nums, val + 1)
        
        prod = 1
        mod = 10**9 + 7
        for val in nums:
            prod = ((prod % mod) * (val % mod)) % mod
        return prod