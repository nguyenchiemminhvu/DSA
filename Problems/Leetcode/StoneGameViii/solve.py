from typing import List

class Solution:
    def stoneGameVIII(self, stones: List[int]) -> int:
        n = len(stones)
        prefix_sum = [0] * (n + 1)
        for i in range(n):
            prefix_sum[i + 1] = prefix_sum[i] + stones[i]
        
        cur_dp = prefix_sum[n]
        for i in range(n - 2, 0, -1):
            cur_dp = max(cur_dp, prefix_sum[i + 1] - cur_dp)
        return cur_dp