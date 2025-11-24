from typing import List

class Solution:
    def arraySign(self, nums: List[int]) -> int:
        count_neg, count_pos = 0, 0
        for val in nums:
            if val == 0:
                return 0
            elif val < 0:
                count_neg += 1
            else:
                count_pos += 1
        
        return -1 if (count_neg & 1) else 1