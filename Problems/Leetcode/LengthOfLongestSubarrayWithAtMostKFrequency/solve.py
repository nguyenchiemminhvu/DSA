from collections import defaultdict
from typing import List

class Solution:
    def maxSubarrayLength(self, nums: List[int], k: int) -> int:
        # import heapq
        # f = defaultdict(int)
        # pq = [] # (-freq, val)
        # res = 0
        # n = len(nums)
        # l = 0
        # for r in range(n):
        #     f[nums[r]] += 1
        #     heapq.heappush(pq, (-f[nums[r]], nums[r]))
        #     while pq and -pq[0][0] > k:
        #         while pq and -pq[0][0] != f[pq[0][1]]:
        #             heapq.heappop(pq)
        #         if pq and -pq[0][0] > k:
        #             f[nums[l]] -= 1
        #             if f[nums[l]] > 0:
        #                 heapq.heappush(pq, (-f[nums[l]], nums[l]))
        #             l += 1
        #     res = max(res, r - l + 1)
        # return res

        f = defaultdict(int)
        n = len(nums)
        res = 0
        l = 0
        for r in range(n):
            val = nums[r]
            f[val] += 1
            while f[val] > k:
                f[nums[l]] -= 1
                l += 1
            res = max(res, r - l + 1)
        return res