from typing import List

class Solution:
    def grayCode(self, n: int) -> List[int]:
        arr = []
        for i in range(1 << n):
            arr.append(i ^ (i >> 1))
        return arr