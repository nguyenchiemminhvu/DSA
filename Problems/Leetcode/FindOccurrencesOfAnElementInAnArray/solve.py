from typing import List

class Solution:
    def occurrencesOfElement(self, nums: List[int], queries: List[int], x: int) -> List[int]:
        indexes = []
        for i, val in enumerate(nums):
            if val == x:
                indexes.append(i)
        
        res = []
        for query in queries:
            if query > len(indexes):
                res.append(-1)
            else:
                res.append(indexes[query - 1])
        return res