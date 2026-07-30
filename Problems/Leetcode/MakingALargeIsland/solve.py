from collections import defaultdict
from typing import List

class Solution:
    def largestIsland(self, grid: List[List[int]]) -> int:
        cell_to_region = defaultdict(lambda: int(-1))
        region_to_size = defaultdict(int)
        
        m, n = len(grid), len(grid[0])
        def dfs(r, c, region_id):
            if r < 0 or r >= m or c < 0 or c >= n:
                return 0
            if grid[r][c] == 0:
                return 0
            cell_to_region[(r, c)] = region_id
            grid[r][c] = 0
            return 1 \
                + dfs(r - 1, c, region_id) \
                + dfs(r + 1, c, region_id) \
                + dfs(r, c - 1, region_id) \
                + dfs(r, c + 1, region_id)
        
        res = 0
        region_id = 0
        for r in range(m):
            for c in range(n):
                if grid[r][c] == 1:
                    region_id += 1
                    size = dfs(r, c, region_id)
                    region_to_size[region_id] = size
                    res = max(res, size)
        
        for r in range(m):
            for c in range(n):
                if cell_to_region[(r, c)] == -1:
                    sum_size = 1
                    s_id = set()
                    for nr, nc in [(r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)]:
                        if nr < 0 or nr >= m or nc < 0 or nc >= n:
                            continue
                        s_id.add(cell_to_region[(nr, nc)])
                    for region_id in s_id:
                        sum_size += region_to_size[region_id]
                    res = max(res, sum_size)
        
        return res