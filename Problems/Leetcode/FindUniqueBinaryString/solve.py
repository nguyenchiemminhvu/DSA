from typing import List

class Solution:
    def findDifferentBinaryString(self, nums: List[str]) -> str:
        n = len(nums)
        s = set([int(val, 2) for val in nums])
        for val in range((1 << n)):
            if val not in s:
                res = bin(val)[2:]
                return ('0' * (n - len(res))) + res
        return ""