from typing import List

class Solution:
    def onesMinusZeros(self, grid: List[List[int]]) -> List[List[int]]:
        m, n = len(grid), len(grid[0])

        row_ones = [0] * m
        row_zero = [0] * m
        col_ones = [0] * n
        col_zero = [0] * n

        for i in range(m):
            for j in range(n):
                if grid[i][j] == 0:
                    row_zero[i] += 1
                    col_zero[j] += 1
                else:
                    row_ones[i] += 1
                    col_ones[j] += 1
        
        diff = [[0] * n for _ in range(m)]
        for i in range(m):
            for j in range(n):
                diff[i][j] = row_ones[i] + col_ones[j] - row_zero[i] - col_zero[j]
        return diff