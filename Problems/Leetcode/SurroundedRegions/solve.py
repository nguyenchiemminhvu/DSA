from typing import List

class Solution:
    def solve(self, grid: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        
        m, n = len(grid), len(grid[0])

        visited = [[False for _ in range(n)] for _ in range(m)]

        def dfs(r: int, c: int):
            visited[r][c] = True
            for nr, nc in [(r-1,c),(r+1,c),(r,c-1),(r,c+1)]:
                if nr >= 0 and nr < m and nc >= 0 and nc < n:
                    if not visited[nr][nc] and grid[nr][nc] == 'O':
                        dfs(nr, nc)
        
        for i in range(m):
            for j in range(n):
                if i == 0 or i == m - 1 or j == 0 or j == n - 1:
                    if not visited[i][j] and grid[i][j] == 'O':
                        dfs(i, j)
        
        for i in range(m):
            for j in range(n):
                if not visited[i][j] and grid[i][j] == 'O':
                    grid[i][j] = 'X'
        