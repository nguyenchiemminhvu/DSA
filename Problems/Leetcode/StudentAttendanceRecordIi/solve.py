class Solution:
    def checkRecord(self, n: int) -> int:
        mod = 10**9 + 7

        # possible attendance records at day i-th with latest late and used absent status
        # from functools import lru_cache
        # @lru_cache(None)
        # def F(i: int, late: int, absent: int) -> int:
        #     if late >= 3 or absent >= 2:
        #         return 0
        #     if i >= n:
        #         return 1
        #     res = 0
        #     res += F(i + 1, 0, absent) % mod # next is P
        #     res += F(i + 1, 0, absent + 1) % mod # next is A
        #     res += F(i + 1, late + 1, absent) % mod # next is L
        #     return res % mod
        # return F(0, 0, 0)

        dp = [[0] * 3 for _ in range(2)]
        dp[0][0] = 1
        for d in range(n):
            next_dp = [[0] * 3 for _ in range(2)]
            for a in range(2):
                for l in range(3):
                    count = dp[a][l]
                    if count == 0:
                        continue
                    
                    next_dp[a][0] = (next_dp[a][0] + count) % mod # next is P
                    if a + 1 < 2:
                        next_dp[a + 1][0] = (next_dp[a + 1][0] + count) % mod # next is A
                    if l + 1 < 3:
                        next_dp[a][l + 1] = (next_dp[a][l + 1] + count) # next is L
            dp = next_dp
        
        res = 0
        for row in dp:
            for val in row:
                res = (res + val) % mod
        return res