from typing import List

class Solution:
    def findBall(self, grid: List[List[int]]) -> List[int]:
        m = len(grid)
        n = len(grid[0])

        res = [-1] * n

        for c in range(n):
            oc = c
            for r in range(m):
                if grid[r][oc] == 1:
                    if oc == n - 1:
                        oc = -1
                        break
                    if grid[r][oc + 1] == -1:
                        oc = -1
                        break
                    oc += 1
                else:
                    if oc == 0:
                        oc = -1
                        break
                    if grid[r][oc - 1] == 1:
                        oc = -1
                        break
                    oc -= 1
            res[c] = oc

        return res