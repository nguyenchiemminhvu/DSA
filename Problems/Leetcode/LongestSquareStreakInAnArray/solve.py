from typing import List

class Solution:
    def longestSquareStreak(self, nums: List[int]) -> int:
        n = len(nums)
        nums.sort(reverse=True)

        longest = -1

        s = set()
        for val in nums:
            s.add(val)

            length = 1
            p = val
            while p * p in s:
                p = p * p
                length += 1
            if length >= 2:
                longest = max(longest, length)
        
        return longest