class Solution:
    def isSameAfterReversals(self, num: int) -> bool:
        def reverse(val: int) -> int:
            res = 0
            while val:
                res = res * 10 + (val % 10)
                val //= 10
            return res
        
        num1 = reverse(num)
        num2 = reverse(num1)
        return num == num2