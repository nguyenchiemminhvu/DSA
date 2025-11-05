from typing import List

class Solution:
    def isToeplitzMatrix(self, mat: List[List[int]]) -> bool:
        m = len(mat)
        n = len(mat[0])
        for i in range(n):
            r = 0
            c = i
            val = mat[r][c]
            while r >= 0 and r < m and c >= 0 and c < n:
                if mat[r][c] != val:
                    return False
                r += 1
                c += 1
        
        for i in range(n):
            r = m - 1
            c = i
            val = mat[r][c]
            while r >= 0 and r < m and c >= 0 and c < n:
                if mat[r][c] != val:
                    return False
                r -= 1
                c -= 1
        
        for i in range(m):
            r = i
            c = 0
            val = mat[r][c]
            while r >= 0 and r < m and c >= 0 and c < n:
                if mat[r][c] != val:
                    return False
                r += 1
                c += 1
        
        for i in range(m):
            r = i
            c = n - 1
            val = mat[r][c]
            while r >= 0 and r < m and c >= 0 and c < n:
                if mat[r][c] != val:
                    return False
                r -= 1
                c -= 1

        return True