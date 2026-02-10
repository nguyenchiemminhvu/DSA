from typing import List

class Solution:
    def longestBalanced(self, nums: List[int]) -> int:
        n = len(nums)
        best = 0

        for l in range(n):
            evens = set()
            odds = set()
            for r in range(l, n):
                x = nums[r]
                if x % 2 == 0:
                    evens.add(x)
                else:
                    odds.add(x)

                if len(evens) == len(odds):
                    best = max(best, r - l + 1)

        return best