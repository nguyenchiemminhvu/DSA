class Solution:
    def checkDivisibility(self, n: int) -> bool:
        temp = n
        s = 0
        p = 1
        while temp:
            d = temp % 10
            s += d
            p *= d
            temp //= 10
        return n % (p + s) == 0