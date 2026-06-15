from typing import List

class Solution:
    def findMaximumXOR(self, nums: List[int]) -> int:
        max_xor = 0
        mask = 0

        for i in range(30, -1, -1):
            mask |= (1 << i)
            prefixes = set()
            for val in nums:
                prefixes.add(val & mask)
            
            candidate = max_xor | (1 << i)
            for val in prefixes:
                if candidate ^ val in prefixes:
                    max_xor = candidate
        
        return max_xor