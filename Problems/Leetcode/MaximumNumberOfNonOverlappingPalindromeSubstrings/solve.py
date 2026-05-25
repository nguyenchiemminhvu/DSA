class Solution:
    def maxPalindromes(self, s: str, k: int) -> int:
        n = len(s)

        dp = [[False] * n for _ in range(n)]
        for i in range(n):
            dp[i][i] = True
            if i > 0 and s[i - 1] == s[i]:
                dp[i - 1][i] = True
        
        for i in range(n):
            l, r = i - 1, i + 1
            while l >= 0 and r < n and s[l] == s[r]:
                dp[l][r] = True
                l -= 1
                r += 1
            
            if i > 0 and dp[i - 1][i]:
                l, r = i - 2, i + 1
                while l >= 0 and r < n and s[l] == s[r]:
                    dp[l][r] = True
                    l -= 1
                    r += 1
        
        mem = {}
        def F(i: int) -> int:
            if i >= n:
                return 0
            if i in mem:
                return mem[i]
            res = F(i + 1)
            for j in range(i + k - 1, n):
                if dp[i][j]:
                    res = max(
                        res,
                        1 + F(j + 1)
                    )
            mem[i] = res
            return res
        
        return F(0)