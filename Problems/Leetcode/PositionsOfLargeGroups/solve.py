from typing import List

class Solution:
    def largeGroupPositions(self, s: str) -> List[List[int]]:
        n = len(s)
        groups = []
        l, r = 0, 0
        while r < n:
            while r + 1 < n and s[r + 1] == s[l]:
                r += 1
            if r - l + 1 >= 3:
                groups.append([l, r])

            r += 1
            l = r
        return groups