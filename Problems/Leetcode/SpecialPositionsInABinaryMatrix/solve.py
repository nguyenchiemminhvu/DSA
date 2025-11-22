from typing import List

class Solution:
    def numSpecial(self, mat: List[List[int]]) -> int:
        count = 0
        m = len(mat)
        n = len(mat[0])
        srows = [0] * m
        scols = [0] * n
        for i in range(m):
            for j in range(n):
                srows[i] += mat[i][j]
                scols[j] += mat[i][j]
        
        for i in range(m):
            for j in range(n):
                if mat[i][j] == 1 and srows[i] == 1 and scols[j] == 1:
                    count += 1
        return count