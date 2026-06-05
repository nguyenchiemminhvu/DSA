from collections import defaultdict
from typing import List

class Solution:
    def findCommonResponse(self, responses: List[List[str]]) -> str:
        s_res = [set(res) for res in responses]
        max_r = 0
        mp = defaultdict(int)
        for res in s_res:
            for r in res:
                mp[r] += 1
                max_r = max(max_r, mp[r])
        
        smallest_res = []
        for k, count in mp.items():
            if count == max_r:
                smallest_res.append(k)
        return min(smallest_res)