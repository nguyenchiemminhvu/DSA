from collections import deque
from typing import List

class Solution:
    def maximumSafenessFactor(self, grid: List[List[int]]) -> int:
        n = len(grid)
        
        if grid[0][0] == 1 or grid[n-1][n-1] == 1:
            return 0

        INF = 0xFFFFFFFF
        dp = [[INF] * n for _ in range(n)]
        q = deque()
        
        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1:
                    dp[i][j] = 0
                    q.append((0, i, j))
        
        # build dp distance table
        max_safeness = 0
        while q:
            d, r, c = q.popleft()
            max_safeness = max(max_safeness, d)
            for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                if nr >= 0 and nr < n and nc >= 0 and nc < n:
                    if grid[nr][nc] == 0 and dp[nr][nc] > d + 1:
                        dp[nr][nc] = d + 1
                        q.append((d + 1, nr, nc))
        
        def can_reach_end(target: int) -> bool:
            if dp[0][0] < target:
                return False
                
            q = deque([(0, 0)])
            visited = [[False] * n for _ in range(n)]
            visited[0][0] = True
            
            while q:
                r, c = q.popleft()
                if r == n - 1 and c == n - 1:
                    return True
                    
                for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                    if 0 <= nr < n and 0 <= nc < n and not visited[nr][nc]:
                        if dp[nr][nc] >= target:
                            visited[nr][nc] = True
                            q.append((nr, nc))
            return False

        left, right = 0, max_safeness
        res = 0
        
        while left <= right:
            mid = left + (right - left) // 2
            
            if can_reach_end(mid):
                res = mid       # 'mid' is a valid safeness factor, record it
                left = mid + 1  # Try searching for a higher valid safeness factor
            else:
                right = mid - 1 # 'mid' is unsafe, look for a lower factor
                
        return res
