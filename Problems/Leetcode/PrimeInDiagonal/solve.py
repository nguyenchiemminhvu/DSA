from typing import List
import math

class Solution:
    def diagonalPrime(self, nums: List[List[int]]) -> int:
        def is_prime(val: int) -> bool:
            if val <= 1:
                return False
            if val == 2:
                return True
            for i in range(2, int(math.sqrt(val)) + 1):
                if val % i == 0:
                    return False
            return True
        
        res = 0
        n = len(nums)
        i = 0
        while i < n:
            val = nums[i][i]
            if is_prime(val):
                res = max(res, val)
            i += 1
        
        i = 0
        while i < n:
            val = nums[i][n - i - 1]
            if is_prime(val):
                res = max(res, val)
            i += 1
        
        return res