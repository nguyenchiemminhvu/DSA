from collections import defaultdict

class Solution:
    def toggleLightBulbs(self, nums: list[int]) -> list[int]:
        freq = defaultdict(int)
        for val in nums:
            freq[val] += 1
        
        res = []
        for k, v in freq.items():
            if v & 1:
                res.append(k)
        return sorted(res)