from typing import List

class Solution:
    def minOperations(self, nums: List[int], k: int) -> int:
        x = 0
        for val in nums:
            x ^= val
        
        diff = x ^ k
        op = 0
        while diff:
            diff = diff & (diff - 1)
            op += 1
        return op