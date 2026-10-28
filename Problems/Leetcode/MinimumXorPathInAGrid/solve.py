class Solution:
    def minCost(self, grid: list[list[int]]) -> int:
        m, n = len(grid), len(grid[0])

        dp = [[set() for _ in range(n)] for _ in range(m)]
        dp[0][0].add(grid[0][0])
        for i in range(1, n):
            for val in dp[0][i - 1]:
                dp[0][i].add(grid[0][i] ^ val)
        for i in range(1, m):
            for val in dp[i - 1][0]:
                dp[i][0].add(grid[i][0] ^ val)
        
        for i in range(1, m):
            for j in range(1, n):
                cands = set()
                cands |= dp[i - 1][j]
                cands |= dp[i][j - 1]
                for val in cands:
                    dp[i][j].add(grid[i][j] ^ val)
        
        return min(dp[m - 1][n - 1])