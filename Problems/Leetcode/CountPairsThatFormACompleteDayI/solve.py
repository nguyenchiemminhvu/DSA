from typing import List
from collections import defaultdict

class Solution:
    def countCompleteDayPairs(self, hours: List[int]) -> int:
        count = 0
        f = defaultdict(int)
        for h in hours:
            count += f[(24 - (h % 24)) % 24]
            f[h % 24] += 1
        return count