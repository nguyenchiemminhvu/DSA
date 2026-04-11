from typing import List

class Solution:
    def minimumDistance(self, nums: List[int]) -> int:
        map_idx = {} # val -> array of indices
        for i, val in enumerate(nums):
            if val not in map_idx:
                map_idx[val] = []
            map_idx[val].append(i)
        
        res = float('inf')
        for val, arr in map_idx.items():
            n = len(arr)
            if n < 3:
                continue
            
            for i in range(2, n):
                res = min(res, (arr[i] - arr[i - 2]) * 2)
        
        return -1 if res == float('inf') else res