from typing import List
import string

class Solution:
    def maximumCostSubstring(self, s: str, chars: str, vals: List[int]) -> int:
        scores = {}
        for c in string.ascii_lowercase:
            val = ord(c) - ord('a') + 1
            scores[c] = val
        for i, c in enumerate(chars):
            scores[c] = vals[i]
        
        n = len(s)

        res = 0
        cur_max = 0
        for c in s:
            cur_max = max(scores[c], cur_max + scores[c])
            res = max(res, cur_max)
        return res