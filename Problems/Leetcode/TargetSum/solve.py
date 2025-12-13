from typing import List

class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        n = len(nums)
        memo = {}
        def generating(idx: int, s: int) -> int:
            if idx >= n:
                return 1 if s == target else 0
            
            if (idx, s) in memo:
                return memo[(idx, s)]
            
            opt1 = generating(idx + 1, s + nums[idx])
            opt2 = generating(idx + 1, s - nums[idx])
            memo[(idx, s)] = opt1 + opt2
            return opt1 + opt2
        
        return generating(0, 0)