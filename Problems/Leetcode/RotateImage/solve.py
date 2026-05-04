from typing import List

class Solution:
    def rotate(self, mat: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        n = len(mat)

        # Transpose matrix in-place
        for i in range(n):
            for j in range(i + 1, n):
                mat[i][j], mat[j][i] = mat[j][i], mat[i][j]

        # Reverse each row in-place (for clockwise rotation)
        for i in range(n):
            mat[i].reverse()