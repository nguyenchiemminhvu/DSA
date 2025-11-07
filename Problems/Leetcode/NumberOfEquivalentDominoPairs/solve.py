from collections import defaultdict
from typing import List

class Solution:
    def numEquivDominoPairs(self, dominoes: List[List[int]]) -> int:
        d = defaultdict(int)
        for dom in dominoes:
            mi, ma = min(dom[0], dom[1]), max(dom[0], dom[1])
            d[(mi, ma)] += 1
        
        res = 0
        for k, v in d.items():
            res += v * (v - 1) // 2
        return res