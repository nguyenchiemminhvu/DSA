from typing import List

class Solution:
    def threeConsecutiveOdds(self, arr: List[int]) -> bool:
        count = 0
        for val in arr:
            if val & 1:
                count += 1
                if count == 3:
                    return True
            else:
                count = 0
        return False