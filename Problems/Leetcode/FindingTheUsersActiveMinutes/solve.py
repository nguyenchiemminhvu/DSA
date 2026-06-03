from typing import List
from collections import defaultdict

class Solution:
    def findingUsersActiveMinutes(self, logs: List[List[int]], k: int) -> List[int]:
        uam = defaultdict(set)
        for i, t in logs:
            uam[i].add(t)

        f = defaultdict(int)
        for _, v in uam.items():
            f[len(v)] += 1
        
        res = [0] * k
        for i in range(1, k + 1):
            res[i - 1] = f[i]
        return res