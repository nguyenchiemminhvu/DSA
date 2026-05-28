from typing import List

class Solution:
    def numOfSubarrays(self, arr: List[int]) -> int:
        mod = 10 ** 9 + 7

        pre_even = 1
        pre_odd = 0
        s = 0
        for val in arr:
            s = (s + val) & 1
            if s:
                pre_odd += 1
            else:
                pre_even += 1
        return ((pre_odd % mod) * (pre_even % mod)) % mod