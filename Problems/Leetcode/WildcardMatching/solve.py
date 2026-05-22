class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        ns = len(s)
        np = len(p)

        # mem = {}
        # def F(idx_s: int, idx_p: int) -> bool:
        #     if idx_s >= ns:
        #         return idx_p >= np or all(c == '*' for c in p[idx_p:])
        #     if idx_p >= np:
        #         return idx_s >= ns
        #     if (idx_s, idx_p) in mem:
        #         return mem[(idx_s, idx_p)]
        #     res = False
        #     if p[idx_p] == '?':
        #         res = res or F(idx_s + 1, idx_p + 1)
        #     elif p[idx_p] == '*':
        #         res = res or (F(idx_s + 1, idx_p + 1) or F(idx_s + 1, idx_p) or F(idx_s, idx_p + 1))
        #     else:
        #         res = res or (s[idx_s] == p[idx_p] and F(idx_s + 1, idx_p + 1))
        #     mem[(idx_s, idx_p)] = res
        #     return res
        # return F(0, 0)

        dp = [[False] * (np + 1) for _ in range(ns + 1)]
        for idx_s in range(ns + 1):
            dp[idx_s][np] = (idx_s >= ns)
        for idx_p in range(np + 1):
            dp[ns][idx_p] = (idx_p >= np) or all(c == '*' for c in p[idx_p:])
        
        for idx_s in range(ns - 1, -1, -1):
            for idx_p in range(np - 1, -1, -1):
                if p[idx_p] == '?':
                    dp[idx_s][idx_p] = dp[idx_s + 1][idx_p + 1]
                elif p[idx_p] == '*':
                    dp[idx_s][idx_p] = dp[idx_s + 1][idx_p + 1] or dp[idx_s + 1][idx_p] or dp[idx_s][idx_p + 1]
                else:
                    dp[idx_s][idx_p] = (s[idx_s] == p[idx_p]) and dp[idx_s + 1][idx_p + 1]
        return dp[0][0]