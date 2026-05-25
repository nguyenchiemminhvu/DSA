class Solution:
    def longestPalindrome(self, s1: str, s2: str) -> int:
        s = s1 + s2
        n = len(s)
        n1, n2 = len(s1), len(s2)
        max_pal = 0

        # mem = {}
        # def F(l: int, r: int) -> int:
        #     nonlocal max_pal
        #     if l > r:
        #         return 0
        #     if l == r:
        #         return 1
        #     if (l, r) in mem:
        #         return mem[(l, r)]
        #     res = 0
        #     if s[l] == s[r]:
        #         res = max(res, 2 + F(l + 1, r - 1))
        #         if l < n1 and r >= n1:
        #             max_pal = max(max_pal, res)
        #     else:
        #         res = max(res, F(l + 1, r), F(l, r - 1))
        #     mem[(l, r)] = res
        #     return res
        # F(0, n - 1)
        # return max_pal

        dp = [[0] * n for _ in range(n)]
        for i in range(n):
            dp[i][i] = 1
        for l in range(n - 1, -1, -1):
            for r in range(l + 1, n):
                if s[l] == s[r]:
                    dp[l][r] = max(dp[l][r], 2 + dp[l + 1][r - 1])
                    if l < n1 and r >= n1:
                        max_pal = max(max_pal, dp[l][r])
                else:
                    dp[l][r] = max(dp[l][r], dp[l + 1][r], dp[l][r - 1])

        return max_pal