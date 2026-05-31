from collections import defaultdict

class Solution:
    def digitFrequencyScore(self, n: int) -> int:
        f = defaultdict(int)
        while n:
            d = n % 10
            f[d] += 1
            n //= 10
        
        res = 0
        for k, v in f.items():
            res += k * v
        return res