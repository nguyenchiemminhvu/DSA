from typing import List

class Solution:
    def jump(self, nums: List[int]) -> int:
        INF = 0x7FFFFFFF
        n = len(nums)
        memo = {}

        # F(i) is the minimum steps to reach i-th index
        def F(i:int) -> int:
            if i <= 0:
                return 0
            
            if i in memo:
                return memo[i]
            
            min_jump = INF
            for j in range(i - 1, -1, -1):
                if j + nums[j] >= i:
                    min_at_j = F(j)
                    if min_at_j != INF:
                        min_jump = min(min_jump, 1 + min_at_j)
            memo[i] = min_jump
            return memo[i]
        
        return F(n - 1)