from collections import deque
from typing import List

class Solution:
    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
        n = len(grid)
        if grid[0][0] == 1:
            return -1

        q = deque([(0, 0)])
        visited = set()
        visited.add((0, 0))

        steps = 0
        while q:
            length = len(q)
            steps += 1
            for _ in range(length):
                r, c = q.popleft()
                if r == n - 1 and c == n - 1:
                    return steps
                
                adjs = [
                    (r + 1, c),
                    (r - 1, c),
                    (r, c + 1),
                    (r, c - 1),
                    (r - 1, c - 1),
                    (r - 1, c + 1),
                    (r + 1, c - 1),
                    (r + 1, c + 1),
                ]
                for nr, nc in adjs:
                    if nr < 0 or nr >= n or nc < 0 or nc >= n:
                        continue
                    if (nr, nc) in visited:
                        continue
                    if grid[nr][nc] == 0:
                        visited.add((nr, nc))
                        q.append((nr, nc))
            
        return -1