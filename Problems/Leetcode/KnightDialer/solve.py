class Solution:
    def knightDialer(self, k: int) -> int:
        mod = 10**9 + 7

        grid = [[0 for j in range(3)] for i in range(4)]
        grid[3][0] = grid[3][2] = -1

        m, n = 4, 3
        dir_r = [ -2, -2, 2, 2, -1, 1, -1, 1 ]
        dir_c = [ -1, 1, -1, 1, -2, -2, 2, 2 ]

        # ====================================
        # mem = {}
        # def F(r: int, c: int, steps: int) -> int:
        #     if r < 0 or r >= m or c < 0 or c >= n or grid[r][c] == -1:
        #         return 0
        #     if steps == k - 1:
        #         return 1
        #     if (r, c, steps) in mem:
        #         return mem[(r, c, steps)]

        #     res = 0
        #     for d in range(8):
        #         nr = r + dir_r[d]
        #         nc = c + dir_c[d]
        #         res += F(nr, nc, steps + 1)

        #     mem[(r, c, steps)] = res % mod
        #     return mem[(r, c, steps)]

        # res = 0
        # for i in range(m):
        #     for j in range(n):
        #         if grid[i][j] != -1:
        #             res += F(i, j, 0)
        # return res % mod

        # =================================
        dp = [[1] * n for _ in range(m)]
        dp[3][0] = dp[3][2] = 0
        for steps in range(1, k):
            next_dp = [[0] * n for _ in range(m)]
            for r in range(m):
                for c in range(n):
                    if grid[r][c] != -1:
                        for d in range(8):
                            nr = r + dir_r[d]
                            nc = c + dir_c[d]
                            if nr >= 0 and nr < m and nc >= 0 and nc < n:
                                if grid[nr][nc] != -1:
                                    next_dp[nr][nc] += dp[r][c]
                                    next_dp[nr][nc] %= mod
            dp = next_dp
        
        res = 0
        for i in range(m):
            for j in range(n):
                res = ((res % mod) + (dp[i][j] % mod)) % mod
        return res % mod