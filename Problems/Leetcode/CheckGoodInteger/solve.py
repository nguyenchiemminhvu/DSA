class Solution:
    def checkGoodInteger(self, n: int) -> bool:
        s = 0
        ss = 0
        while n:
            d = n % 10
            s += d
            ss += d ** 2
            n //= 10
        
        return ss - s >= 50