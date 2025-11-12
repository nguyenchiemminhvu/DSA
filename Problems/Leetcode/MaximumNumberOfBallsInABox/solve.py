class Solution:
    def countBalls(self, lowLimit: int, highLimit: int) -> int:
        def sum_digit(val: int) -> int:
            s = 0
            while val:
                s += (val % 10)
                val //= 10
            return s
        f = {}
        for val in range(lowLimit, highLimit + 1):
            s = sum_digit(val)
            f[s] = f.get(s, 0) + 1
        return max(f.values())