from collections import deque
from typing import List

class Solution:
    def numEnclaves(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        def bfs(start_r, start_c):
            count = 0
            is_enclave = True
            q = deque([(start_r, start_c)])
            grid[start_r][start_c] = 0
            
            while q:
                r, c = q.popleft()
                count += 1
                
                if r == 0 or r == m - 1 or c == 0 or c == n - 1:
                    is_enclave = False
                    
                for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                    if 0 <= nr < m and 0 <= nc < n:
                        if grid[nr][nc] == 1:
                            grid[nr][nc] = 0
                            q.append((nr, nc))
                            
            return count if is_enclave else 0
        
        res = 0
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    res += bfs(i, j)
        return res
