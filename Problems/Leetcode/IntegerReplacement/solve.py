class Solution:
    def integerReplacement(self, n: int) -> int:
        steps = 0
        while n > 1:
            if n & 1:
                if (n > 0b11) and (n & 0b11) == 0b11:
                    n += 1
                else:
                    n -= 1
            else:
                n >>= 1
            steps += 1

        return steps