from collections import deque
from typing import List

class Solution:
    def maxDistance(self, grid: List[List[int]]) -> int:
        n = len(grid)

        q = deque()
        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1:
                    q.append((i, j))
        if not q or len(q) == n * n:
            return -1
        
        dist = -1
        while q:
            size = len(q)
            dist += 1
            for _ in range(size):
                r, c = q.popleft()
                for nr, nc in [(r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)]:
                    if nr < 0 or nr >= n or nc < 0 or nc >= n:
                        continue
                    if grid[nr][nc] == 0:
                        q.append((nr, nc))
                        grid[nr][nc] = 1
        
        return dist