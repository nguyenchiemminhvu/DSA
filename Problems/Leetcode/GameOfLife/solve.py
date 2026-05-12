from typing import List

class Solution:
    def gameOfLife(self, grid: List[List[int]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        directions = [
            (-1, -1), (-1, 0), (-1, 1),
            (0, -1),           (0, 1),
            (1, -1),  (1, 0),  (1, 1)
        ]

        m, n = len(grid), len(grid[0])
        temp = [[0 for _ in range(n)] for _ in range(m)]
        for i in range(m):
            for j in range(n):
                live_neighbors = 0

                for dx, dy in directions:
                    ni, nj = i + dx, j + dy
                    if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 1:
                        live_neighbors += 1

                if grid[i][j] == 1:
                    if live_neighbors == 2 or live_neighbors == 3:
                        temp[i][j] = 1
                    else:
                        temp[i][j] = 0
                else:
                    if live_neighbors == 3:
                        temp[i][j] = 1
                    else:
                        temp[i][j] = 0

        for i in range(m):
            for j in range(n):
                grid[i][j] = temp[i][j]
        