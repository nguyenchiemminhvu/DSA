from typing import List

class Solution:
    def shortestBridge(self, grid: List[List[int]]) -> int:
        n = len(grid)
        groups = []

        temp = []
        def dfs(r, c):
            temp.append((r, c))
            grid[r][c] = 0

            for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                if nr >= 0 and nr < n and nc >= 0 and nc < n:
                    if grid[nr][nc] == 1:
                        dfs(nr, nc)

        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1:
                    temp.clear()
                    dfs(i, j)
                    groups.append(temp[:])
        
        res = 0xFFFFFFFF
        group_a, group_b = groups
        for pa in group_a:
            ra, ca = pa
            for pb in group_b:
                rb, cb = pb
                dist = abs(rb - ra) + abs(cb - ca) - 1
                res = min(res, dist)

        return res