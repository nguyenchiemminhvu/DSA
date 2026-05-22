class Solution:
    def minCut(self, s: str) -> int:
        n = len(s)
        
        dp = [[False for _ in range(n)] for _ in range(n)]
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
            if i <= 0:
                return 0
            if dp[0][i]:
                return 0
            if i in mem:
                return mem[i]
            min_cut = i
            for j in range(1, i + 1):
                if dp[j][i]:
                    min_cut = min(min_cut, 1 + F(j - 1))
            mem[i] = min_cut
            return min_cut
        
        return F(n - 1)