from typing import List

class Solution:
    def modifiedMatrix(self, mat: List[List[int]]) -> List[List[int]]:
        m = len(mat)
        n = len(mat[0])
        cols = [-1] * n
        for c in range(n):
            for row in mat:
                cols[c] = max(cols[c], row[c])
        
        for i in range(m):
            for j in range(n):
                if mat[i][j] == -1:
                    mat[i][j] = cols[j]
        return mat