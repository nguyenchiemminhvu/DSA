class Solution:
    def minInsertions(self, s: str) -> int:
        n = len(s)

        # mem = {}
        # def F(l: int, r: int) -> int:
        #     if l >= r:
        #         return 0
        #     if (l, r) in mem:
        #         return mem[(l, r)]
        #     min_steps = float('inf')
        #     if s[l] == s[r]:
        #         min_steps = min(min_steps, F(l + 1, r - 1))
        #     else:
        #         min_steps = min(min_steps, 1 + min(F(l + 1, r), F(l, r - 1)))
        #     mem[(l, r)] = min_steps
        #     return min_steps
        # return F(0, n - 1)

        dp = [[float('inf') for _ in range(n + 1)] for _ in range(n + 1)]
        for l in range(n):
            for r in range(l + 1):
                dp[l][r] = 0    
        
        for l in range(n - 1, -1, -1):
            for r in range(l, n):
                if s[l] == s[r]:
                    dp[l][r] = min(dp[l][r], dp[l + 1][r - 1])
                else:
                    dp[l][r] = min(dp[l][r], 1 + min(dp[l + 1][r], dp[l][r - 1]))

        return dp[0][n - 1]