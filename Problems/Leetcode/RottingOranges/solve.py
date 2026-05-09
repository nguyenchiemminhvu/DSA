from typing import List
from collections import deque

class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        def dfs() -> int:
            q = deque()

            # get all rotten fruit positions
            total_fruit = 0
            rotten_fruit = 0
            for i in range(m):
                for j in range(n):
                    if grid[i][j] == 1:
                        total_fruit += 1
                    if grid[i][j] == 2:
                        total_fruit += 1
                        rotten_fruit += 1
                        q.append((i, j))
            
            if rotten_fruit == total_fruit:
                return 0
            
            times = 0
            while q:
                size = len(q)
                for _ in range(size):
                    r, c = q.popleft()
                    for nr, nc in [(r-1, c), (r+1, c), (r, c-1), (r, c+1)]:
                        if nr >= 0 and nr < m and nc >= 0 and nc < n:
                            if grid[nr][nc] == 1:
                                rotten_fruit += 1
                                grid[nr][nc] = 2
                                q.append((nr, nc))
                
                times += 1
                if rotten_fruit == total_fruit:
                    return times
            
            return -1
        
        return dfs()