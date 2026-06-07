from collections import defaultdict
from typing import List

class Solution:
    def findRepeatedDnaSequences(self, s: str) -> List[str]:
        n = len(s)
        mp = defaultdict(int)
        for i in range(n - 9):
            mp[s[i:i + 10]] += 1
        
        res = []
        for k, count in mp.items():
            if count > 1:
                res.append(k)

        return res