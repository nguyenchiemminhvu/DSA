from typing import List

class Solution:
    def distinctDifferenceArray(self, nums: List[int]) -> List[int]:
        n = len(nums)
        s = set()
        prefix = [0] * n
        for i in range(n):
            s.add(nums[i])
            prefix[i] = len(s)
        
        s = set()
        suffix = [0] * n
        for i in range(n - 1, -1, -1):
            suffix[i] = len(s)
            s.add(nums[i])

        dist = [0] * n
        for i in range(n):
            dist[i] = prefix[i] - suffix[i]
        return dist