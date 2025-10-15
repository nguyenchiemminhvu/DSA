from typing import List

class Solution:
    def findContentChildren(self, g: List[int], s: List[int]) -> int:
        g.sort()
        s.sort()
        ig = 0
        iz = 0
        while ig < len(g) and iz < len(s):
            if g[ig] > s[iz]:
                iz += 1
            else:
                ig += 1
                iz += 1
        return ig