from typing import List

class Solution:
    def countPermutations(self, arr: List[int]) -> int:
        if min(arr[1:]) <= arr[0]:
            return 0
        
        mod = 10**9 + 7
        n = len(arr) - 1
        prod = 1
        for i in range(n):
            prod = ((prod % mod) * ((i + 1) % mod)) % mod
        return prod