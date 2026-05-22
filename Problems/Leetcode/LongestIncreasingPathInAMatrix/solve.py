from typing import List

class Solution:
    def longestIncreasingPath(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        # mem = {}
        # def F(r: int, c: int) -> int:
        #     if r < 0 or r >= m or c < 0 or c >= n:
        #         return 0
        #     if (r, c) in mem:
        #         return mem[(r, c)]
        #     res = 1
        #     for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
        #         if nr < 0 or nr >= m or nc < 0 or nc >= n:
        #             continue
        #         if grid[nr][nc] < grid[r][c]:
        #             res = max(res, 1 + F(nr, nc))
        #     mem[(r, c)] = res
        #     return res
        # res = 0
        # for r in range(m):
        #     for c in range(n):
        #         res = max(res, F(r, c))
        # return res

        cells = [(grid[r][c], r, c) for r in range(m) for c in range(n)]
        cells.sort(key=lambda x: x[0])

        dp = [[1] * n for _ in range(m)]
        for i in range(len(cells)):
            val, r, c = cells[i]
            for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                if nr >= 0 and nr < m and nc >= 0 and nc < n:
                    if val < grid[nr][nc]:
                        dp[nr][nc] = max(dp[nr][nc], 1 + dp[r][c])
        return max(max(row) for row in dp)