from typing import List

class Solution:
    def findKDistantIndices(self, nums: List[int], key: int, k: int) -> List[int]:
        key_idx = []
        for i, val in enumerate(nums):
            if val == key:
                key_idx.append(i)
        
        res = []
        n = len(nums)
        for idx in key_idx:
            res.extend([i for i in range(max(0, idx - k), min(n - 1, idx + k) + 1)])
        return list(set(res))