from typing import Set

class Solution:
    def sumOfPrimesInRange(self, n: int) -> int:
        def get_primes(limit: int) -> Set[int]:
            primes = [True] * (limit + 1)
            primes[0] = primes[1] = False
            for i in range(2, int(limit ** 0.5) + 1):
                if primes[i]:
                    for j in range(i * i, limit + 1, i):
                        primes[j] = False
            return set([i for i in range(limit + 1) if primes[i]])
        
        rev = int(str(n)[::-1])
        left = min(n, rev)
        right = max(n, rev)
        primes = get_primes(right + 1)
        res = 0
        for val in range(left, right + 1):
            if val in primes:
                res += val
        return res