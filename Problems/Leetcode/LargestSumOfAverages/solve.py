from typing import List

class Solution:
    def largestSumOfAverages(self, nums: List[int], k: int) -> float:
        n = len(nums)

        prefix_sum = [0] * (n + 1)
        for i in range(n):
            prefix_sum[i + 1] = prefix_sum[i] + nums[i]
        
        def segment_avg(l: int, r: int) -> float:
            return (prefix_sum[r + 1] - prefix_sum[l]) / (r - l + 1)
        
        mem = {}
        def F(i: int, cnt: int) -> float:
            if i >= n:
                return 0.0
            
            if cnt == 1:
                return segment_avg(i, n - 1)
            
            if (i, cnt) in mem:
                return mem[(i, cnt)]
            
            res = 0.0
            for j in range(i + 1, n - cnt + 2):
                res = max(
                    res,
                    segment_avg(i, j - 1) + F(j, cnt - 1)
                )
            
            mem[(i, cnt)] = res
            return res
        
        return F(0, k)