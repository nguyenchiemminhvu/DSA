from typing import List

class Solution:
    def zigzagTraversal(self, grid: List[List[int]]) -> List[int]:
        offset = 0
        res = []
        for row in grid:
            vals = []
            for i in range(offset, len(row), 2):
                vals.append(row[i])
            if offset & 1:
                vals.reverse()
            res.extend(vals)
            offset = (offset + 1) % 2
        return res