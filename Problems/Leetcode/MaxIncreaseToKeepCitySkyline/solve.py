from typing import List

class Solution:
    def maxIncreaseKeepingSkyline(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        max_rows = [0] * m
        max_cols = [0] * n
        for r in range(m):
            for c in range(n):
                max_rows[r] = max(max_rows[r], grid[r][c])
                max_cols[c] = max(max_cols[c], grid[r][c])
        
        res = 0
        for r in range(m):
            for c in range(n):
                res += min(max_rows[r], max_cols[c]) - grid[r][c]
        return res