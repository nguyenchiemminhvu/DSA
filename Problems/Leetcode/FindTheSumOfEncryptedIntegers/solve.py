from typing import List

class Solution:
    def sumOfEncryptedInt(self, nums: List[int]) -> int:
        def encrypt(val: int) -> int:
            digits = []
            count = 0
            while val:
                digits.append(val % 10)
                val //= 10
                count += 1
            d = max(digits)
            res = 0
            while count:
                res = res * 10 + d
                count -= 1
            return res
        
        s = 0
        for val in nums:
            s += encrypt(val)
        return s