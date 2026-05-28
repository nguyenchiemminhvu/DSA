from typing import List

class Solution:
    def countPrimes(self, n: int) -> int:
        if n < 2:
            return 0

        # Create a boolean array "is_prime[0..n]" and initialize
        # all entries it as true. 
        is_prime = [True] * (n + 1)
        is_prime[0] = is_prime[1] = False  # 0 and 1 are not prime
        
        # Check numbers from 2 up to the square root of n
        for p in range(2, int(n**0.5) + 1):
            if is_prime[p]:
                # Mark all multiples of p starting from p*p as False
                # Smaller multiples have already been marked by smaller primes
                for i in range(p * p, n + 1, p):
                    is_prime[i] = False
                    
        # Collect all indices that remained True
        return sum([1 for p in range(n + 1) if p < n and is_prime[p]])