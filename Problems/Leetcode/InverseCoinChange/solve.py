from typing import List

class Solution:
    def findCoins(self, dp: List[int]) -> List[int]:
        dp = [1] + dp
        ndp = len(dp)

        res = []
        for c in range(1, ndp):
            if dp[c] == 1:
                res.append(c)
                for j in range(ndp - 1, c - 1, -1):
                    dp[j] -= dp[j - c]
        
        return res if sum(dp[1:]) == 0 else []