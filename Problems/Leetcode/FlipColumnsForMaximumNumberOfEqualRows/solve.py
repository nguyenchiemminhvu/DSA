from collections import defaultdict
from typing import List

class Solution:
    def maxEqualRowsAfterFlips(self, grid: List[List[int]]) -> int:
        # mp[tuple(row)] denotes the number of row appears in the grid
        mp = defaultdict(int)
        for row in grid:
            mp[tuple(row)] += 1
        
        res = 0
        for row in grid:
            flip = [(val + 1) % 2 for val in row]
            res = max(res, mp[tuple(row)] + mp[tuple(flip)])
        return res