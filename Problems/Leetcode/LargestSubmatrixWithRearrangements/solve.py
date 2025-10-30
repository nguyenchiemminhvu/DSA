from typing import List

class Solution:
    def largestSubmatrix(self, mat: List[List[int]]) -> int:
        m = len(mat)
        n = len(mat[0])
        for c in range(n):
            count = 0
            for r in range(m):
                if mat[r][c] == 1:
                    count += 1
                    mat[r][c] = count
                else:
                    count = 0
        
        new_mat = [sorted(row, reverse=True) for row in mat]
        res = 0
        for row in new_mat:
            horizontal = 1
            for height in row:
                res = max(res, height * horizontal)
                horizontal += 1

        return res