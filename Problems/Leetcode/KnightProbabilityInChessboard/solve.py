class Solution:
    def knightProbability(self, n: int, k: int, r: int, c: int) -> float:
        dir_r = [-2, -2, -1, -1, 1, 1, 2, 2]
        dir_c = [-1, 1, -2, 2, -2, 2, -1, 1]

        dp = [[0] * n for _ in range(n)]
        dp[r][c] = 1

        for step in range(k):
            next_state = [[0] * n for _ in range(n)]
            for r in range(n):
                for c in range(n):
                    for d in range(8):
                        nr, nc = r + dir_r[d], c + dir_c[d]
                        if nr >= 0 and nr < n and nc >= 0 and nc < n:
                            next_state[nr][nc] += dp[r][c] / 8.0
            dp = next_state
        
        res = 0.0
        for row in dp:
            res += sum(row)
        return res