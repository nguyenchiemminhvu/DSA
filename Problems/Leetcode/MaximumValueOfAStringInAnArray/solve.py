from typing import List

class Solution:
    def maximumValue(self, strs: List[str]) -> int:
        res = 0
        for s in strs:
            try:
                val = int(s)
                res = max(res, val)
            except ValueError:
                res = max(res, len(s))
        return res