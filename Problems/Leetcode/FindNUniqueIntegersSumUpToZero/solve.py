from typing import List

class Solution:
    def sumZero(self, n: int) -> List[int]:
        if n == 1:
            return [0]
        return [-i for i in range(1, n)] + [((n - 1) * n) // 2]