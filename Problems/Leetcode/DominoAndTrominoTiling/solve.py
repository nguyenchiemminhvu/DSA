class Solution:
    def numTilings(self, n: int) -> int:
        mod = 10**9 + 7

        # mem = {}
        # def F(i: int) -> int:
        #     if i <= 0:
        #         return 0
        #     if i == 1:
        #         return 1
        #     if i == 2:
        #         return 2
        #     if i == 3:
        #         return 5
        #     if i in mem:
        #         return mem[i]
        #     ret = 2 * F(n - 1) + F(n - 3)
        #     mem[i] = ret
        #     return ret
        # return F(n) % mod

        if n <= 0: return 0
        if n == 1: return 1
        if n == 2: return 2
        if n == 3: return 5
        a, b, c = 1, 2, 5
        for i in range(n - 3):
            a, b, c = b, c, (2 * c + a) % mod
        return c