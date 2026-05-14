from typing import List

class Solution:
    def maxPathScore(self, grid: List[List[int]], k: int) -> int:
        m, n = len(grid), len(grid[0])
        
        # mem = {}
        # def F(r: int, c: int, cost: int) -> int:
        #     if r >= m or c >= n:
        #         return -1
        #     need_cost = int(grid[r][c] != 0)
        #     if cost + need_cost > k:
        #         return -1
        #     if r == m - 1 and c == n - 1:
        #         return grid[r][c]
        #     if (r, c, cost) in mem:
        #         return mem[(r, c, cost)]
        #     right = F(r, c + 1, cost + need_cost)
        #     down = F(r + 1, c, cost + need_cost)
        #     res = -1
        #     if right != -1:
        #         res = max(res, grid[r][c] + right)
        #     if down != -1:
        #         res = max(res, grid[r][c] + down)
        #     mem[(r, c, cost)] = res
        #     return res
        # return F(0, 0, 0)

        dp = [[[-1] * (k + 2) for _ in range(n + 1)] for _ in range(m + 1)]
        for cost in range(k + 1):
            need_cost = (grid[m - 1][n - 1] != 0)
            if cost + need_cost <= k:
                dp[m - 1][n - 1][cost] = grid[m - 1][n - 1]
        
        for r in range(m - 1, -1, -1):
            for c in range(n - 1, -1, -1):
                need_cost = (grid[r][c] != 0)
                for cost in range(k, -1, -1):
                    right = dp[r][c + 1][cost + need_cost]
                    if right != -1:
                        dp[r][c][cost] = max(dp[r][c][cost], grid[r][c] + right)
                    down = dp[r + 1][c][cost + need_cost]
                    if down != -1:
                        dp[r][c][cost] = max(dp[r][c][cost], grid[r][c] + down)
        return dp[0][0][0]