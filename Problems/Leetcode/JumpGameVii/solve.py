class Solution:
    def canReach(self, s: str, min_jump: int, max_jump: int) -> bool:
        n = len(s)
        if s[-1] == '1':
            return False
        
        # from functools import lru_cache
        # @lru_cache
        # def F(i: int) -> bool:
        #     if i < 0 or s[i] == '1':
        #         return False
        #     if i == 0:
        #         return True
        #     prev_l = max(0, i - max_jump)
        #     prev_r = i - min_jump
        #     if prev_l > prev_r:
        #         return False
        #     for j in range(prev_l, prev_r + 1):
        #         if F(j):
        #             return True
        #     return False
        # return F(n - 1)

        dp = [False] * n
        dp[0] = True
        count = 0
        for i in range(1, n):
            r = i - min_jump
            if r >= 0 and dp[r] == True:
                count += 1
            l = i - max_jump - 1
            if l >= 0 and dp[l] == True:
                count -= 1
            
            if s[i] == '0' and count > 0:
                dp[i] = True
        return dp[n - 1]