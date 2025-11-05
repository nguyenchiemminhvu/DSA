from typing import List

class Solution:
    def diagonalSum(self, mat: List[List[int]]) -> int:
        res = 0
        n = len(mat)
        r, c = 0, 0
        while r >= 0 and r < n and c >= 0 and c < n:
            res += mat[r][c]
            r += 1
            c += 1
        
        r, c = 0, n - 1
        while r >= 0 and r < n and c >= 0 and c < n:
            res += mat[r][c]
            r += 1
            c -= 1
        
        if n & 1:
            center = n >> 1
            res -= mat[center][center]
        return res