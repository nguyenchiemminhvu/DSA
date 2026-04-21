from typing import List

class Solution:
    def firstStableIndex(self, nums: list[int], k: int) -> int:
        n = len(nums)
        prefix = [[val, val] for val in nums]
        for i in range(1, n):
            prefix[i][0] = max(prefix[i - 1][0], prefix[i][0])
        for i in range(n - 2, -1, -1):
            prefix[i][1] = min(prefix[i + 1][1], prefix[i][1])
        
        for i in range(n):
            stable = prefix[i][0] - prefix[i][1]
            if stable <= k:
                return i
        return -1