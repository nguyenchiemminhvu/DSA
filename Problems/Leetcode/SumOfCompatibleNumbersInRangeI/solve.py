class Solution:
    def sumOfGoodIntegers(self, n: int, k: int) -> int:
        res = 0
        for x in range(max(0, n - k), n + k + 1):
            if n & x == 0:
                res += x
        return res