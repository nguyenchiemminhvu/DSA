from typing import List
import math

class Solution:
    def areaOfMaxDiagonal(self, arr: List[List[int]]) -> int:
        arr.sort(key=lambda x: -math.sqrt(x[0]**2 + x[1]**2))
        res = 0
        longest = math.sqrt(arr[0][0]**2 + arr[0][1]**2)
        for a, b in arr:
            diag = math.sqrt(a**2 + b**2)
            area = a * b
            if diag < longest:
                break
            res = max(res, area)
        return res