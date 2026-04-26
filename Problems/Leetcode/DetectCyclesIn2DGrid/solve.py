from typing import List

class Solution:
    def containsCycle(self, grid: List[List[str]]) -> bool:
        m, n = len(grid), len(grid[0])
        visited = [[False] * n for _ in range(m)]
        
        def dfs(r, c, pr, pc, char):
            # mark current as visited
            visited[r][c] = True
            
            # explore 4 directions
            for dr, dc in [(1,0), (-1,0), (0,1), (0,-1)]:
                nr, nc = r + dr, c + dc
                
                # bounds + same character check
                if 0 <= nr < m and 0 <= nc < n and grid[nr][nc] == char:
                    
                    # skip the previous cell (important!)
                    if nr == pr and nc == pc:
                        continue
                    
                    # if already visited → cycle found
                    if visited[nr][nc]:
                        return True
                    
                    # continue DFS
                    if dfs(nr, nc, r, c, char):
                        return True
            
            return False
        
        # try starting DFS from every cell
        for i in range(m):
            for j in range(n):
                if not visited[i][j]:
                    if dfs(i, j, -1, -1, grid[i][j]):
                        return True
        
        return False