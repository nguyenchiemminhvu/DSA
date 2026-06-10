class Solution:
    def shortestPalindrome(self, s: str) -> str:
        n = len(s)

        # dp = [[False] * n for _ in range(n)]
        # for i in range(n):
        #     dp[i][i] = True
        #     if i > 0 and s[i - 1] == s[i]:
        #         dp[i - 1][i] = True
        
        # for i in range(n):
        #     l, r = i - 1, i + 1
        #     while l >= 0 and r < n and dp[l + 1][r - 1]:
        #         if s[l] == s[r]:
        #             dp[l][r] = True
        #         l -= 1
        #         r += 1
            
        #     if i > 0:
        #         l, r = i - 2, i + 1
        #         while l >= 0 and r < n and dp[l + 1][r - 1]:
        #             if s[l] == s[r]:
        #                 dp[l][r] = True
        #             l -= 1
        #             r += 1
        
        # pivot = 0
        # for i in range(n):
        #     if dp[0][i]:
        #         pivot = i
        
        # return s[pivot + 1:][::-1] + s

        for i in range(n - 1, -1, -1):
            if s[0:i + 1] == s[0:i + 1][::-1]:
                return s[i + 1:][::-1] + s
        return ''