class Solution:
    def largestInteger(self, n: int, s: int) -> int:
        res = 0
        while n > 0 and s > 0:
            cand = min(9, s)
            res = res * 10 + cand
            s -= cand
            n -= 1
        
        if n == 0 and s > 0:
            return -1
        
        while n:
            res *= 10
            n -= 1
        return res