from typing import List
import heapq
from collections import defaultdict

class Solution:
    def mostFrequentIDs(self, nums: List[int], freq: List[int]) -> List[int]:
        n = len(nums)
        res = [0] * n
        counter = defaultdict(int)
        pq = []
        for i in range(n):
            val, f = nums[i], freq[i]            
            counter[val] += f
            while pq and pq[0][1] == val:
                heapq.heappop(pq)
            while pq and (counter[pq[0][1]] == 0 or counter[pq[0][1]] != -pq[0][0]):
                heapq.heappop(pq)
            if counter[val] != 0:
                heapq.heappush(pq, (-counter[val], val))
            if pq:
                res[i] = -pq[0][0]
        return res