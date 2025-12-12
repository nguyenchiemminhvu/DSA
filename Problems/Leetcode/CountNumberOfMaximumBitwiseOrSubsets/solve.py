from typing import List

class Solution:
    def countMaxOrSubsets(self, nums: List[int]) -> int:
        OR = 0
        for val in nums:
            OR |= val
        
        n = len(nums)
        count = 0
        def generating(idx: int, tmp: List[int]) -> None:
            if idx >= n:
                tmp_or = 0
                for val in tmp:
                    tmp_or |= val
                if tmp_or == OR:
                    nonlocal count
                    count += 1
                return
            generating(idx + 1, tmp)
            generating(idx + 1, tmp + [nums[idx]])
            
        generating(0, [])
        return count