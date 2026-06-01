from typing import List

class Solution:
    def diagonalSort(self, mat: List[List[int]]) -> List[List[int]]:
        m, n = len(mat), len(mat[0])

        def sort_diag(r_start: int, c_start: int) -> List[int]:
            res = []
            r, c = r_start, c_start
            while r < m and c < n:
                res.append(mat[r][c])
                r += 1
                c += 1
            res.sort()
            r, c = r_start, c_start
            for i in range(len(res)):
                mat[r + i][c + i] = res[i]
            return res

        for i in range(m):
            r, c = i, 0
            sort_diag(r, c)
        
        for j in range(1, n):
            r, c = 0, j
            sort_diag(r, c)
        
        return mat
