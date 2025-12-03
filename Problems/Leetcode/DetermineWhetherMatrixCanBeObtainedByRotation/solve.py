from typing import List

class Solution:
    def findRotation(self, mat: List[List[int]], target: List[List[int]]) -> bool:
        def equal(a: List[List[int]], b: List[List[int]]) -> bool:
            na, nb = len(a), len(b)
            if na != nb:
                return False
            return all(a[i] == b[i] for i in range(na))
        
        def rotate(mat: List[List[int]]) -> None:
            n = len(mat)
            for i in range(n):
                for j in range(i, n):
                    mat[i][j], mat[j][i] = mat[j][i], mat[i][j]
            for i in range(n):
                mat[i].reverse()
        
        for _ in range(4):
            rotate(mat)
            if equal(mat, target):
                return True
        return False
