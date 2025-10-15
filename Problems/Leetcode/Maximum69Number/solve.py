class Solution:
    def maximum69Number (self, num: int) -> int:
        def reverse_num(val:int) -> int:
            res = 0
            while val:
                res = res * 10 + (val % 10)
                val //= 10
            return res
        
        def reverse_and_replace(val:int) -> int:
            res = 0
            k = 1
            while val:
                digit = (val % 10)
                if digit == 6 and k > 0:
                    k -= 1
                    digit = 9
                res = res * 10 + digit
                val //= 10
            return res

        num = reverse_num(num)
        return reverse_and_replace(num)