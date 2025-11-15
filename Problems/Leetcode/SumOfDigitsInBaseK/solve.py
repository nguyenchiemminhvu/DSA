class Solution:
    def sumBase(self, n: int, k: int) -> int:
        def sum_digit_base(val: int, base: int) -> int:
            res = 0
            while val:
                res += (val % base)
                val //= base
            return res
        
        return sum_digit_base(n, k)