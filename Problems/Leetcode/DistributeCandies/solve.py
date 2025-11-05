from typing import List

class Solution:
    def distributeCandies(self, types: List[int]) -> int:
        f = {}
        for t in types:
            f[t] = f.get(t, 0) + 1
        threshold = len(types) // 2
        return min(threshold, len(f.keys()))