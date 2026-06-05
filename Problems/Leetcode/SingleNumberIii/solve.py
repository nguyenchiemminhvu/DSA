from typing import List

class Solution:
    def singleNumber(self, nums: List[int]) -> List[int]:
        x = 0
        for val in nums:
            x ^= val
        
        # find diff bit index
        i = 0
        while x & (1 << i) == 0:
            i += 1
        
        group1 = 0 # all numbers with bit i-th equal 0
        group2 = 0 # all numbers with bit i-th equal 1
        for val in nums:
            if val & (1 << i) == 0:
                group1 ^= val
            else:
                group2 ^= val
        
        return [group1, group2]