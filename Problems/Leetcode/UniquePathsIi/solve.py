from typing import List

class Solution:
    def uniquePathsWithObstacles(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        
        # mem = {}
        # def F(r: int, c: int) -> int:
        #     if r < 0 or c < 0:
        #         return 0
        #     if grid[r][c] == 1:
        #         return 0
        #     if r == 0 and c == 0:
        #         return 1
        #     if (r, c) in mem:
        #         return mem[(r, c)]
        #     count = F(r - 1, c) + F(r, c - 1)
        #     mem[(r, c)] = count
        #     return count
        # return F(m - 1, n - 1)

        dp = [[0 for _ in range(n)] for _ in range(m)]
        meet_obj = False
        for i in range(m):
            if grid[i][0] == 1:
                meet_obj = True
            dp[i][0] = 0 if meet_obj else 1
        meet_obj = False
        for i in range(n):
            if grid[0][i] == 1:
                meet_obj = True
            dp[0][i] = 0 if meet_obj else 1
        
        for i in range(1, m):
            for j in range(1, n):
                if grid[i][j] == 1:
                    dp[i][j] = 0
                else:
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1]
        return dp[m - 1][n - 1]