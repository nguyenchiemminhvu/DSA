from typing import List

class Solution:
    def numberOfSubmatrices(self, grid: List[List[str]]) -> int:
        m = len(grid)
        n = len(grid[0])

        mat = [[[1 if c == 'X' else 0, 1 if c == 'Y' else 0] for c in row] for row in grid]
        for i in range(m):
            for j in range(n):
                if i > 0:
                    mat[i][j][0] += mat[i-1][j][0]
                    mat[i][j][1] += mat[i-1][j][1]
                if j > 0:
                    mat[i][j][0] += mat[i][j-1][0]
                    mat[i][j][1] += mat[i][j-1][1]
                if i > 0 and j > 0:
                    mat[i][j][0] -= mat[i-1][j-1][0]
                    mat[i][j][1] -= mat[i-1][j-1][1]
        
        count = 0
        for i in range(m):
            for j in range(n):
                if mat[i][j][0] > 0 and mat[i][j][0] == mat[i][j][1]:
                    count += 1
        return count