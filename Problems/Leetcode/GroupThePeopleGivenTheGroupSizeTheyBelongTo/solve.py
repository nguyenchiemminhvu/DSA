from typing import List

class Solution:
    def groupThePeople(self, groupSizes: List[int]) -> List[List[int]]:
        pairs = [(val, i) for i, val in enumerate(groupSizes)]
        pairs.sort(key=lambda g: g[0])

        res = []
        i = 0
        n = len(groupSizes)
        while i < n:
            block = pairs[i:i + pairs[i][0]]
            res.append([p[1] for p in block])
            i += len(block)
        return res