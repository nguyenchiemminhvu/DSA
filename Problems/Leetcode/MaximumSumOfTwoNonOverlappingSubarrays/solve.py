from typing import List

class Solution:
    def maxSumTwoNoOverlap(self, nums: List[int], n1: int, n2: int) -> int:
        n = len(nums)

        prefix_sum = [0] * (n + 1)
        for i in range(n):
            prefix_sum[i + 1] = prefix_sum[i] + nums[i]
        
        def F(n1: int, n2: int) -> int:
            res = 0
            for i in range(n - n1 + 1):
                s_from_i = prefix_sum[i + n1] - prefix_sum[i]
                for j in range(i + n1, n - n2 + 1):
                    s_from_j = prefix_sum[j + n2] - prefix_sum[j]
                    res = max(res, s_from_i + s_from_j)    
            return res
        
        return max(F(n1, n2), F(n2, n1))