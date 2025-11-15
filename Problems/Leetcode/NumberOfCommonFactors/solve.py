import math

class Solution:
    def commonFactors(self, a: int, b: int) -> int:
        g = math.gcd(a, b)

        count = 0
        for val in range(1, g + 1):
            if a % val == 0 and b % val == 0:
                count += 1
        return count