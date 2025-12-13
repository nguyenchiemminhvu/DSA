from typing import List

class Solution:
    def combinationSum2(self, nums: List[int], target: int) -> List[List[int]]:
        nums.sort()
        n = len(nums)

        res = []
        def generating(idx: int, tmp: List[int], remain: int) -> None:
            if remain == 0:
                res.append(tmp[:])
                return
            
            for i in range(idx, n):    
                if i > idx and nums[i] == nums[i - 1]:
                    continue
                
                if nums[i] > remain:
                    break
                
                tmp.append(nums[i])
                generating(i + 1, tmp, remain - nums[i])
                tmp.pop()
        
        generating(0, [], target)
        return res