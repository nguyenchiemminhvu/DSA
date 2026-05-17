class Solution:
    def longestIdealString(self, s: str, k: int) -> int:
        n = len(s)

        # mem = {}
        # def F(i: int) -> int:
        #     if i < 0:
        #         return 0
        #     if i in mem:
        #         return mem[i]
        #     res = 1
        #     ival = ord(s[i])
        #     for j in range(i):
        #         jval = ord(s[j])
        #         if abs(ival - jval) <= k:
        #             res = max(res, 1 + F(j))
        #     mem[i] = res
        #     return res
        # res = 1
        # for i in range(n):
        #     res = max(res, F(i))
        # return res

        dp = [1] * n
        res = 1
        last_idx = {}
        for i in range(n):
            ival = ord(s[i])
            for j in range(ival - k, ival + k + 1):
                jch = chr(j)
                if jch in last_idx:
                    jidx = last_idx[jch]
                    dp[i] = max(dp[i], 1 + dp[jidx])
            last_idx[s[i]] = i
            res = max(res, dp[i])
        return res