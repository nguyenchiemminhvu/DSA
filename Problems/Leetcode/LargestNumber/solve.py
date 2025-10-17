from functools import cmp_to_key
from typing import List

class Solution:
    def largestNumber(self, nums: List[int]) -> str:
        def compare_factor(x:int, y:int) -> int:
            xx = str(x)
            yy = str(y)
            if xx + yy > yy + xx:
                return -1
            elif xx + yy < yy + xx:
                return 1
            return 0
        
        nums.sort(key=cmp_to_key(compare_factor))
        res = "".join(map(str, nums))
        return "0" if res[0] == '0' else res