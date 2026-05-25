class Solution:
    def checkPartitioning(self, s: str) -> bool:
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

        def check_palin(l:int, r:int) -> bool:
            return dp[l][r]

        mem = {}
        def F(i: int, cnt: int) -> bool:
            if cnt == 1:
                return check_palin(i, n - 1)
            if (i, cnt) in mem:
                return mem[(i, cnt)]
            
            res = False
            for j in range(i + 1, n - cnt + 2):
                if check_palin(i, j - 1) and F(j, cnt - 1):
                    res = True
                    break
            mem[(i, cnt)] = res
            return res
        
        return F(0, 3)