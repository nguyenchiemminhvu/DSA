# https://leetcode.com/problems/compare-version-numbers

class Solution:
    def compareVersion(self, version1: str, version2: str) -> int:
        L1 = list(map(lambda s: int(s), version1.split('.')))
        L2 = list(map(lambda s: int(s), version2.split('.')))
        if (len(L1) < len(L2)):
            L1 += [0] * (len(L2) - len(L1))
        if (len(L1) > len(L2)):
            L2 += [0] * (len(L1) - len(L2))
        
        for i in range(0, len(L1)):
            if (L1[i] < L2[i]):
                return -1
            if (L1[i] > L2[i]):
                return 1
        return 0
