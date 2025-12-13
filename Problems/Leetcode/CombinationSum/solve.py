from typing import List

class Solution:
    def combinationSum(self, nums: List[int], target: int) -> List[List[int]]:
        nums.sort()
        n = len(nums)
        res = []
        def generating(idx: int, tmp: List[int], s: int) -> None:
            if s > target:
                return
            
            if s == target:
                res.append([val for val in tmp])
                return
            
            if idx >= n:
                return
            
            for i in range(idx, n):
                generating(i, tmp + [nums[i]], s + nums[i])
        
        generating(0, [], 0)
        return res