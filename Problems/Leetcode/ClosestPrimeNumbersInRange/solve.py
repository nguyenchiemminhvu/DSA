from collections import deque
from typing import List

class Solution:
    def closestPrimes(self, left: int, right: int) -> List[int]:
        primes = [True] * (right + 1)
        primes[0] = primes[1] = False
        for p in range(2, int((right + 1) ** 0.5) + 1):
            if primes[p]:
                for i in range(p * p, right + 1, p):
                    primes[i] = False
        
        res = [-1, -1]
        min_dist = float('inf')
        q = deque()
        for i in range(left, right + 1):
            if primes[i]:
                q.append(i)
                if len(q) >= 2:
                    if q[-1] - q[-2] < min_dist:
                        min_dist = q[-1] - q[-2]
                        res = [q[-2], q[-1]]
                    q.popleft()
        return res