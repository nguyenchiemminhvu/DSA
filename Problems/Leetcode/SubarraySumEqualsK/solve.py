from collections import defaultdict
from typing import List

class Solution:
    def subarraySum(self, nums: List[int], k: int) -> int:
        mp = defaultdict(int)
        mp[0] = 1

        res = 0
        s = 0
        for val in nums:
            s += val
            need = s - k
            if need in mp:
                res += mp[need]
            mp[s] += 1
        
        return res