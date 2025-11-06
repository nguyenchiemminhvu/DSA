from typing import List

class Solution:
    def isArraySpecial(self, nums: List[int]) -> bool:
        pairity = nums[0] & 1
        for val in nums:
            if val & 1 != pairity:
                return False
            pairity = (pairity + 1) & 1
        return True