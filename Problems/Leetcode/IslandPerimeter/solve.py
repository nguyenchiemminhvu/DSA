from collections import deque
from typing import List

class Solution:
    def islandPerimeter(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])

        def bfs(r, c) -> int:
            m = len(grid)
            n = len(grid[0])
            q = deque([(r, c)])
            grid[r][c] = 2
            P = 0
            while q:
                r, c = q.popleft()
                p = 4
                near = [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]
                for cell in near:
                    next_r, next_c = cell
                    if next_r >= 0 and next_r < m and next_c >= 0 and next_c < n:
                        if grid[next_r][next_c] != 0:
                            p -= 1
                            if grid[next_r][next_c] != 2:
                                q.append((next_r, next_c))
                                grid[next_r][next_c] = 2
                P += p
            return P

        total_p = 0
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    total_p += bfs(i, j)
        return total_p