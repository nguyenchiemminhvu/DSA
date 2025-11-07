class Solution:
    def tribonacci(self, n: int) -> int:
        a, b, c = 0, 1, 1

        if n == 0:
            return a
        if n == 1:
            return b
        if n == 2:
            return c
        
        while n > 2:
            a, b, c = b, c, a + b + c
            n -= 1
        return c