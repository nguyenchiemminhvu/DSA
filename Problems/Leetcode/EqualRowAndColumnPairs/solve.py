from typing import List
from collections import defaultdict

class Solution:
    def equalPairs(self, grid: List[List[int]]) -> int:
        row_map = defaultdict(int)
        for row in grid:
            row_map[tuple(row)] += 1

        res = 0
        for i in range(len(grid)):
            col_tup = tuple([row[i] for row in grid])
            res += row_map[col_tup]
        
        return res