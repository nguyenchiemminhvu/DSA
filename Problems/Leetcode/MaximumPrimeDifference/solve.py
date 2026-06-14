from typing import List

class Solution:
    def maximumPrimeDifference(self, nums: List[int]) -> int:
        def sieve_primes(limit: int) -> set[int]:
            masks = [True] * (limit + 1)
            masks[0] = masks[1] = False
            for p in range(2, int(limit ** 0.5) + 1):
                if masks[p]:
                    for i in range(p * p, limit + 1, p):
                        masks[i] = False
            
            return set(i for i in range(2, limit + 1) if masks[i])

        primes = sieve_primes(max(nums) + 1)
        mp = []
        for i in range(len(nums)):
            if nums[i] in primes:
                mp.append(i)

        return mp[-1] - mp[0]