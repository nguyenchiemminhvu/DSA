from typing import List

class Solution:
    def stoneGameVII(self, stones: List[int]) -> int:
        n = len(stones)
        prefix_sum = [0] * (n + 1)
        for i in range(n):
            prefix_sum[i + 1] = prefix_sum[i] + stones[i]
        
        # mem = {}
        # def F(l: int, r: int) -> int:
        #     if l >= r:
        #         return 0
        #     if (l, r) in mem:
        #         return mem[(l, r)]
        #     left = (prefix_sum[r] - prefix_sum[l]) - F(l, r - 1)
        #     right = (prefix_sum[r + 1] - prefix_sum[l + 1]) - F(l + 1, r)
        #     res = max(left, right)
        #     mem[(l, r)] = res
        #     return res
        # return F(0, n - 1)

        # dp[i] represents the max score difference for a subarray starting at index i
        dp = [0] * n
        
        # Iterate over all possible lengths of subarrays starting from length 2 up to n
        for length in range(2, n + 1):
            # Update dp array from right to left to reuse values from the previous length
            for l in range(n - length + 1):
                r = l + length - 1
                
                # Option 1: Remove rightmost stone
                left = (prefix_sum[r] - prefix_sum[l]) - dp[l]
                # Option 2: Remove leftmost stone
                right = (prefix_sum[r + 1] - prefix_sum[l + 1]) - dp[l + 1]
                
                dp[l] = max(left, right)
                
        return dp[0]