from typing import List, Optional, Tuple

class Solution:
    def numDecodings(self, s: str) -> int:
        n = len(s)
        encoded = set(str(val) for val in range(1, 27))

        # mem = {}
        # def F(i: int) -> int:
        #     if i >= n:
        #         return 1
        #     if i in mem:
        #         return mem[i]
        #     ways = 0
        #     op1 = s[i:i+1]
        #     if op1 in encoded:
        #         ways += F(i + 1)
        #     if i + 2 <= n:
        #         op2 = s[i:i+2]
        #         if op2 in encoded:
        #             ways += F(i + 2)
        #     mem[i] = ways
        #     return ways
        # return F(0)

        dp = [0 for _ in range(n + 2)]
        dp[n] = dp[n + 1] = 1
        for i in range(n - 1, -1, -1):
            op1 = s[i:i + 1]
            if op1 in encoded:
                dp[i] += dp[i + 1]
            
            if i + 2 <= n:
                op2 = s[i:i + 2]
                if op2 in encoded:
                    dp[i] += dp[i + 2]
        
        return dp[0]