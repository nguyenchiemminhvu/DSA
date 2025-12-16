from typing import List

class Solution:
    def getMaximumGold(self, grid: List[List[int]]) -> int:
        max_gold = 0
        m = len(grid)
        n = len(grid[0])
        visited = set()
        opts = []
        def dfs(r: int, c: int, cur_gold: int) -> None:
            if r < 0 or r >= m or c < 0 or c >= n:
                opts.append(cur_gold)
                return
            if grid[r][c] == 0:
                opts.append(cur_gold)
                return
            
            for nr, nc in [(r+1, c), (r-1, c), (r, c+1), (r, c-1)]:
                if (nr * n + nc) not in visited:
                    visited.add(nr * n + nc)
                    dfs(nr, nc, cur_gold + grid[r][c])
                    visited.remove(nr * n + nc)

        for i in range(m):
            for j in range(n):
                visited = set()
                opts = []
                visited.add(i * n + j)
                dfs(i, j, 0)
                if opts:
                    max_gold = max(max_gold, max(opts))
        return max_gold