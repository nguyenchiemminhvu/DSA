from collections import Counter
from typing import List

class Solution:
    def findMatrix(self, nums: list[int]) -> list[list[int]]:
        res = []
        counter = Counter(nums)
        new_row_added = False
        while True:
            row = []
            for k, v in counter.items():
                if v > 0:
                    row.append(k)
                    counter[k] -= 1
            if not row:
                break
            res.append(row)
        return res