from typing import List

class Solution:
    def captureForts(self, forts: List[int]) -> int:
        n = len(forts)
        our_forts = []
        for i in range(n):
            if forts[i] == 1:
                our_forts.append(i)

        res = 0
        # left to right
        for start in our_forts:
            count = 0
            for i in range(start + 1, n):
                if forts[i] == 0:
                    count += 1
                elif forts[i] == 1:
                    break
                elif forts[i] == -1:
                    res = max(res, count)
                    break

        # right to left
        for start in reversed(our_forts):
            count = 0
            for i in range(start - 1, -1, -1):
                if forts[i] == 0:
                    count += 1
                elif forts[i] == 1:
                    break
                elif forts[i] == -1:
                    res = max(res, count)
                    break

        return res