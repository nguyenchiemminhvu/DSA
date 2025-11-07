import math

class Solution:
    def numPrimeArrangements(self, n: int) -> int:
        def count_primes_up_to_n(n):
            if n < 2:
                return 0
            is_prime = [True] * (n + 1)
            is_prime[0] = is_prime[1] = False
            for p in range(2, int(n**0.5) + 1):
                if is_prime[p]:
                    for multiple in range(p * p, n + 1, p):
                        is_prime[multiple] = False
            count = 0
            for i in range(2, n + 1):
                if is_prime[i]:
                    count += 1
            return count
        
        primes = count_primes_up_to_n(n)
        primes_permu = math.factorial(primes) % int(1e9 + 7)
        normal = n - primes
        normal_permu = math.factorial(normal) % int(1e9 + 7)
        return (primes_permu * normal_permu) % int(1e9 + 7)