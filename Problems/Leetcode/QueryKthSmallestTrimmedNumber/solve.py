from typing import List
import heapq

class Solution:
    def smallestTrimmedNumbers(self, nums: List[str], queries: List[List[int]]) -> List[int]:
        res = []
        for query in queries:
            k, trim = query
            arr = []
            for i, val in enumerate(nums):
                trimmed = val[-trim:]
                heapq.heappush(arr, (-int(trimmed),-i))
                if len(arr) > k:
                    heapq.heappop(arr)
            res.append(-arr[0][1])
        return res