from typing import List

class Solution:
    def pathExistenceQueries(self, n: int, nums: List[int], k: int, queries: List[List[int]]) -> List[bool]:
        groups = [0] * n
        cur_id = 0
        for i in range(1, n):
            if nums[i] - k > nums[i - 1]:
                cur_id += 1
            groups[i] = cur_id
        
        res = []
        for u, v in queries:
            res.append(groups[u] == groups[v])
        return res