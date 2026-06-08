from typing import List

class Solution:
    def addSpaces(self, s: str, spaces: List[int]) -> str:
        prev = 0

        res = []
        for space_idx in spaces:
            res.append(s[prev:space_idx])
            prev = space_idx
        res.append(s[prev:])
        return ' '.join(res)