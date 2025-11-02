from typing import List

class Solution:
    def countKDifference(self, nums: List[int], k: int) -> int:
        freq = {}
        for val in sorted(nums):
            freq[val] = freq.get(val, 0) + 1
        
        count = 0
        for val, f in freq.items():
            count += freq[val] * freq.get(val + k, 0)
        return count