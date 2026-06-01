from typing import List

class Solution:
    def rearrangeArray(self, nums: List[int]) -> List[int]:
        n = len(nums)

        res = [0] * n
        i, j = 0, 1
        for val in nums:
            if val > 0:
                res[i] = val
                i += 2
            else:
                res[j] = val
                j += 2
        
        return res