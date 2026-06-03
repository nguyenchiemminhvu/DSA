from typing import List

class Solution:
    def countDistinctIntegers(self, nums: List[int]) -> int:
        s = set(nums)
        for val in nums:
            s.add(int(str(val)[::-1]))
        return len(s)