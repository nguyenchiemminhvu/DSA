class Solution:
    def findPaths(self, m: int, n: int, max_move: int, start_r: int, start_c: int) -> int:
        mod = 10**9 + 7

        # mem = {}
        # def F(r: int, c: int, cur_move: int) -> int:
        #     nonlocal mod
        #     if cur_move > max_move:
        #         return 0
        #     if r < 0 or r >= m or c < 0 or c >= n:
        #         return 1
        #     if (r, c, cur_move) in mem:
        #         return mem[(r, c, cur_move)]
        #     ways = 0
        #     for nr, nc in [(r + 1, c),(r - 1, c),(r, c + 1),(r, c - 1)]:
        #         ways = ((ways % mod) + (F(nr, nc, cur_move + 1) % mod)) % mod
        #     mem[(r, c, cur_move)] = ways
        #     return ways
        # return F(start_r, start_c, 0) % mod

        res = 0

        dp = [[0] * n for _ in range(m)]
        dp[start_r][start_c] = 1

        for k in range(max_move):
            new_dp = [[0] * n for _ in range(m)]

            for r in range(m):
                for c in range(n):
                    if dp[r][c] > 0:
                        ways = dp[r][c]
                        for nr, nc in [(r + 1, c),(r - 1, c),(r, c + 1),(r, c - 1)]:
                            if nr < 0 or nr >= m or nc < 0 or nc >= n:
                                res = (res + ways) % mod
                            else:
                                new_dp[nr][nc] = (new_dp[nr][nc] + ways) % mod
            
            dp = new_dp
        
        return res