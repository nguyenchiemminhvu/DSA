from typing import List
from collections import Counter, defaultdict

class Solution:
    def specialTriplets(self, nums: List[int]) -> int:
        res = 0
        mod = 10**9 + 7
        prefix = defaultdict(int)
        suffix = Counter(nums)
        for val in nums:
            suffix[val] -= 1
            res = (res % mod + (prefix[val * 2] * suffix[val * 2]) % mod) % mod
            prefix[val] += 1
        return res