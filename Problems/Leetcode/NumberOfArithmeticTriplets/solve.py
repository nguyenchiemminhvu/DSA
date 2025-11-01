from typing import List

class Solution:
    def arithmeticTriplets(self, nums: List[int], diff: int) -> int:
        freq = {}
        for val in nums:
            freq[val] = freq.get(val, 0) + 1
        
        count = 0
        for val, f in freq.items():
            f1 = freq.get(val + diff, 0)
            f2 = freq.get(val + diff + diff, 0)
            count += (f * f1 * f2)
        return count