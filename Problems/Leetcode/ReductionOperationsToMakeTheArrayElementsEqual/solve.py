from typing import List

class Solution:
    def reductionOperations(self, nums: List[int]) -> int:
        n = len(nums)
        nums.sort(reverse=True)
        
        res = 0
        count = 0
        i = 0
        while i < n:
            j = i
            while j < n and nums[j] == nums[i]:
                count += 1
                j += 1
            
            i = j
            if i < n:
                res += count
        
        return res