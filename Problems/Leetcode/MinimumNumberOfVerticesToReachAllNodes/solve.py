from collections import defaultdict
from typing import List

class Solution:
    def findSmallestSetOfVertices(self, n: int, edges: List[List[int]]) -> List[int]:
        res = []
        mp = defaultdict(int)
        for u, v in edges:
            mp[v] += 1
        for i in range(n):
            if i not in mp:
                res.append(i)
        return res