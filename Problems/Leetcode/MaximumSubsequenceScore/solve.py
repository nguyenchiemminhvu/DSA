from typing import List
import heapq

class Solution:
    def maxScore(self, nums1: List[int], nums2: List[int], k: int) -> int:
        n = len(nums1)
        pairs = [(p[0], p[1]) for p in zip(nums2, nums1)]
        pairs.sort(key=lambda x: x[0], reverse=True)

        pq = []
        for i in range(k - 1):
            heapq.heappush(pq, pairs[i][1])

        res = 0
        s = sum(pq)
        for i in range(k - 1, n):
            val2, val1 = pairs[i]
            s += val1
            heapq.heappush(pq, val1)
            if len(pq) > k:
                s -= heapq.heappop(pq)
            res = max(res, val2 * s)
        return res