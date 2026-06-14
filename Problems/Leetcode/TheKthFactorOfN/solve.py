from typing import List

class Solution:
    def kthFactor(self, n: int, k: int) -> int:
        def get_factors(val: int) -> list[int]:
            factors = set()
            for i in range(1, int(val ** 0.5) + 1):
                if val % i == 0:
                    factors.add(i)
                    factors.add(val // i)
            return sorted(list(factors))
        
        factors = get_factors(n)
        return -1 if k - 1 >= len(factors) else factors[k - 1]