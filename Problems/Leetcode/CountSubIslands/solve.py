from typing import List

class Solution:
    def countSubIslands(self, grid1: List[List[int]], grid2: List[List[int]]) -> int:
        m, n = len(grid1), len(grid1[0])

        def dfs_visit(r, c, visited):
            if r < 0 or r >= m or c < 0 or c >= n:
                return
            if grid2[r][c] == 0:
                return
            if (r, c) in visited:
                return
            visited.add((r, c))
            for nr, nc in [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]:
                dfs_visit(nr, nc, visited)

        count = 0
        for r in range(m):
            for c in range(n):
                if grid2[r][c] == 1:
                    visited = set()
                    dfs_visit(r, c, visited)

                    is_sub = True
                    for vr, vc in visited:
                        if grid1[vr][vc] == 0:
                            is_sub = False
                            break
                    count += int(is_sub)

                    for vr, vc in visited:
                        grid2[vr][vc] = 0
        return count