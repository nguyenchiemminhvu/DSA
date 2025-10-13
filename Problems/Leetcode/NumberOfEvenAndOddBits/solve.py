from typing import List

class Solution:
    def evenOddBit(self, n: int) -> List[int]:
        idx = 0
        counter = [0] * 2
        while n:
            counter[idx] += (n & 1)
            idx = (idx + 1) % 2
            n >>= 1
        return counter