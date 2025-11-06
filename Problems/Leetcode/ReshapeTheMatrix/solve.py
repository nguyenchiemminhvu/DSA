from typing import List

class Solution:
    def matrixReshape(self, mat: List[List[int]], r: int, c: int) -> List[List[int]]:
        m = len(mat)
        n = len(mat[0])
        if m * n != r * c:
            return mat
        
        res = [[0] * c for _ in range(r)]
        for i in range(m):
            for j in range(n):
                idx = i * n + j
                res[(idx // c)][(idx % c)] = mat[i][j]
        return res
