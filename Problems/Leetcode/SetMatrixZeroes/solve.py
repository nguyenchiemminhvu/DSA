from typing import List

class Solution:
    def setZeroes(self, mat: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        m, n = len(mat), len(mat[0])
        mask_row = [False] * m
        mask_col = [False] * n
        
        for i in range(m):
            for j in range(n):
                if mat[i][j] == 0:
                    mask_row[i] = True
                    mask_col[j] = True
        
        for i in range(m):
            for j in range(n):
                if mask_row[i] or mask_col[j]:
                    mat[i][j] = 0