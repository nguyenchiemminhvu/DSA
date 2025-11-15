from typing import List

class Solution:
    def deleteGreatestValue(self, grid: List[List[int]]) -> int:
        n = len(grid[0])
        grid = [sorted(row) for row in grid]

        res = 0
        for i in range(n - 1, -1, -1):
            res += max(row[i] for row in grid)
        return res