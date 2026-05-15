from typing import List

class Solution:
    def rob(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 1:
            return nums[0]

        mem = {}
        def F(i: int, n: int) -> int:
            if i >= n:
                return 0
            if i in mem:
                return mem[i]
            max_robbed = 0
            max_robbed = max(max_robbed, nums[i] + F(i + 2, n)) # pick this house
            max_robbed = max(max_robbed, F(i + 1, n)) # skip this house
            mem[i] = max_robbed
            return max_robbed
        
        op1 = F(0, n - 1)
        mem = {}
        op2 = F(1, n)
        return max(op1, op2)