from typing import List

class Solution:
    def largestMagicSquare(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])

        def check(r: int, c: int, k: int) -> bool:
            # Target sum = sum of first row
            target = sum(grid[r][c:c+k])

            # Check all rows
            for i in range(r, r + k):
                if sum(grid[i][c:c+k]) != target:
                    return False

            # Check all columns
            for j in range(c, c + k):
                col_sum = 0
                for i in range(r, r + k):
                    col_sum += grid[i][j]
                if col_sum != target:
                    return False

            # Check main diagonal
            diag1 = 0
            for i in range(k):
                diag1 += grid[r + i][c + i]
            if diag1 != target:
                return False

            # Check anti-diagonal
            diag2 = 0
            for i in range(k):
                diag2 += grid[r + i][c + k - 1 - i]
            if diag2 != target:
                return False

            return True
        
        res = 0
        for k in range(1, n + 1):
            for i in range(m - k + 1):
                for j in range(n - k + 1):
                    if check(i, j, k):
                        res = max(res, k)
        return res