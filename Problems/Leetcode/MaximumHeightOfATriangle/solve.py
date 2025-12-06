from typing import List

class Solution:
    def maxHeightOfTriangle(self, red: int, blue: int) -> int:
        def compute_row(count: List[int]) -> int:
            row = 0
            idx = 0
            req = 1
            while count[idx] >= req:
                row += 1
                count[idx] -= req
                req += 1
                idx = (idx + 1) % 2
            return row
        
        res = 0
        res = max(res, compute_row([red, blue]))
        res = max(res, compute_row([blue, red]))
        return res