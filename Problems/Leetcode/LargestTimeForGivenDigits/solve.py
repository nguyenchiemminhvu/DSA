from typing import List
from collections import Counter

class Solution:
    def largestTimeFromDigits(self, arr: List[int]) -> str:
        hours = [f"{val:02d}" for val in range(23, -1, -1)]
        minutes = [f"{val:02d}" for val in range(59, -1, -1)]

        f_arr = Counter(arr)
        for h in hours:
            for m in minutes:
                tmp = [int(c) for c in h + m]
                f_tmp = Counter(tmp)
                if f_tmp == f_arr:
                    return h + ":" + m
        return ""