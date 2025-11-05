from typing import List

class Solution:
    def maxCount(self, m: int, n: int, ops: List[List[int]]) -> int:
        if not ops:
            return m * n
        mina = min(op[0] for op in ops)
        minb = min(op[1] for op in ops)
        return mina * minb