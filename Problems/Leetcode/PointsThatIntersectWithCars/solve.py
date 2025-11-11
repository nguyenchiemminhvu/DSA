from typing import List

class Solution:
    def numberOfPoints(self, nums: List[List[int]]) -> int:
        prefix = [0] * 111
        for left, right in nums:
            prefix[left] += 1
            prefix[right + 1] -= 1
        
        for i in range(1, 111):
            prefix[i] += prefix[i - 1]
        
        return sum(1 for val in prefix if val > 0)