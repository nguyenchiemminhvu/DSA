from typing import List

class Solution:
    def hasValidPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        
        d_map = {
            1: [(0, -1), (0, 1)],
            2: [(-1, 0), (1, 0)],
            3: [(0, -1), (1, 0)],
            4: [(0, 1), (1, 0)],
            5: [(-1, 0), (0, -1)],
            6: [(-1, 0), (0, 1)]
        }
        
        visited = set()
        
        def dfs(i, j):
            if (i, j) == (m - 1, n - 1):
                return True
            
            visited.add((i, j))
            
            for dx, dy in d_map[grid[i][j]]:
                ni, nj = i + dx, j + dy
                
                if 0 <= ni < m and 0 <= nj < n and (ni, nj) not in visited:
                    if (-dx, -dy) in d_map[grid[ni][nj]]:
                        if dfs(ni, nj):
                            return True
            
            return False
        
        return dfs(0, 0)