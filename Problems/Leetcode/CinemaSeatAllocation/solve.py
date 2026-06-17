from collections import defaultdict
from typing import List

class Solution:
    def maxNumberOfFamilies(self, n: int, reserved: List[List[int]]) -> int:
        res = 2 * n

        mp_row = defaultdict(list)
        for row, seat in reserved:
            mp_row[row].append(seat)

        for row, arr in mp_row.items():
            opt1, opt2, opt3 = 1, 1, 1
            for seat in arr:
                if 2 <= seat <= 5:
                    opt1 = 0
                if 4 <= seat <= 7:
                    opt2 = 0
                if 6 <= seat <= 9:
                    opt3 = 0
            
            max_opt = max(opt1 + opt3, opt2)
            res -= (2 - max_opt)
        return res