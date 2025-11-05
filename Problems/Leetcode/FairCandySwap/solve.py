from typing import List

class Solution:
    def fairCandySwap(self, a: List[int], b: List[int]) -> List[int]:
        sa = sum(a)
        sb = sum(b)
        target = (sb - sa) // 2
        # y = target + x
        bb = set(b)
        for val in a:
            if target + val in bb:
                return [val, target + val]
        return []