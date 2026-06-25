from typing import List

class Solution:
    def countMajoritySubarrays(self, nums: List[int], target: int) -> int:
        n = len(nums)
        prefix_count = [0] * (n + 1)
        for i, val in enumerate(nums):
            temp = int(val == target)
            prefix_count[i + 1] = prefix_count[i] + temp
        
        res = 0
        for i in range(n):
            for j in range(i, n):
                count = prefix_count[j + 1] - prefix_count[i]
                length = j - i + 1
                if length < count * 2:
                    res += 1

        return res