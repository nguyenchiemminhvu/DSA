from typing import List
from collections import deque

class Solution:
    def nearestExit(self, grid: List[List[str]], start: List[int]) -> int:
        m, n = len(grid), len(grid[0])

        def bfs() -> int:
            steps = 0
            q = deque()
            q.append((start[0], start[1]))
            visited = [[False] * n for i in range(m)]
            visited[start[0]][start[1]] = True
            while q:
                size = len(q)
                for _ in range(size):
                    r, c = q.popleft()

                    # is at the border
                    if (r == 0 or r == m - 1 or c == 0 or c == n - 1):
                        if grid[r][c] == '.':
                            if r != start[0] or c != start[1]:
                                return steps
                    
                    for nr, nc in [(r-1, c), (r+1, c), (r, c-1), (r, c+1)]:
                        if nr >= 0 and nr < m and nc >= 0 and nc < n:
                            if grid[nr][nc] == '.' and not visited[nr][nc]:
                                visited[nr][nc] = True
                                q.append((nr, nc))
                steps += 1
            
            return -1
        
        return bfs()