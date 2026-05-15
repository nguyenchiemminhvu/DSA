from typing import List
import bisect

class Solution:
    def maxEnvelopes(self, pairs: List[List[int]]) -> int:
        n = len(pairs)
        pairs.sort(key=lambda x: (x[0], -x[1]))

        tails = []
        for w, h in pairs:
            idx = bisect.bisect_left(tails, h)
            if idx == len(tails):
                tails.append(h)
            else:
                tails[idx] = h
        return len(tails)