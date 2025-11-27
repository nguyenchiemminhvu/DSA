from typing import List

class Solution:
    def maxSubarraySum(self, nums: List[int], k: int) -> int:
        min_prefix = [float('inf')] * k
        min_prefix[0] = 0      
        res = float('-inf')
        cur_sum = 0
        for i in range(len(nums)):
            cur_sum += nums[i]
            cur_mod = (i + 1) % k
            if min_prefix[cur_mod] != float('inf'):
                res = max(res, cur_sum - min_prefix[cur_mod])
            min_prefix[cur_mod] = min(min_prefix[cur_mod], cur_sum)
        return res