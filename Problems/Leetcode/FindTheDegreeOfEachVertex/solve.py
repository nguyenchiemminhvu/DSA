from typing import List

class Solution:
    def findDegrees(self, mat: list[list[int]]) -> list[int]:
        n = len(mat)
        deg = [0] * n
        for i in range(n):
            for j in range(i + 1, n):
                if mat[i][j]:
                    deg[i] += 1
                    deg[j] += 1

        return deg