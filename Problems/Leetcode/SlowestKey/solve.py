from typing import List
from collections import defaultdict
import string

class Solution:
    def slowestKey(self, releaseTimes: List[int], keysPressed: str) -> str:
        d = defaultdict(int)
        prev_time = 0
        for i, k in enumerate(keysPressed):
            d[k] = max(d[k], releaseTimes[i] - prev_time)
            prev_time = releaseTimes[i]
        
        res = '#'
        max_d = 0
        for c in string.ascii_lowercase:
            if max_d <= d[c]:
                max_d = d[c]
                res = c
        return res