from typing import List
from collections import defaultdict

class Solution:
    def largestCombination(self, candidates: List[int]) -> int:
        # mp[i] -> list of values having bit i-th set
        mp = defaultdict(list)
        for val in candidates:
            i = 0
            while i < 24:
                if val & (1 << i):
                    mp[i].append(val)
                i += 1
        
        return max(len(v) for k, v in mp.items())