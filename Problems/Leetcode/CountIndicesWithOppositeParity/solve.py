from typing import List
from collections import defaultdict

class Solution:
    def countOppositeParity(self, nums: list[int]) -> list[int]:
        m = defaultdict(int)
        n = len(nums)
        res = [0] * n
        for i in range(n - 1, -1, -1):
            parity = nums[i] & 1
            res[i] = m[(parity + 1) % 2]
            m[parity] += 1
        return res