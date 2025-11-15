from typing import List

class Solution:
    def luckyNumbers(self, matrix: List[List[int]]) -> List[int]:
        m = len(matrix)
        n = len(matrix[0])
        rows = [min(row) for row in matrix]
        cols = [max(row[c] for row in matrix) for c in range(n)]

        res = []
        for i in range(m):
            for j in range(n):
                if matrix[i][j] == rows[i] and matrix[i][j] == cols[j]:
                    res.append(matrix[i][j])
        return res