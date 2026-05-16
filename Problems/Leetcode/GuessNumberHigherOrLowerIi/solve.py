class Solution:
    def getMoneyAmount(self, n: int) -> int:
        mem = {}
        def F(l: int, r: int) -> int:
            if l >= r:
                return 0
            if (l, r) in mem:
                return mem[(l, r)]
            res = float('inf')
            for x in range(l, r + 1):
                res = min(res, x + max(F(l, x - 1), F(x + 1, r)))
            mem[(l, r)] = res
            return res
        return F(1, n)