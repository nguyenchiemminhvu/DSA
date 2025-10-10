from typing import List

class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        m = len(grid)
        n = len(grid[0])
        visited = [[False for _ in range(n)] for _ in range(m)]

        def bfs(r:int, c:int) -> None:
            Q = [(r, c)]
            visited[r][c] = True
            while len(Q) > 0:
                cur_r, cur_c = Q.pop(0)
                neighbors = [(cur_r - 1, cur_c), (cur_r + 1, cur_c), (cur_r, cur_c - 1), (cur_r, cur_c + 1)]
                for neighbor in neighbors:
                    next_r, next_c = neighbor
                    if next_r >= 0 and next_r < m and next_c >= 0 and next_c < n:
                        if grid[next_r][next_c] == '1' and not visited[next_r][next_c]:
                            visited[next_r][next_c] = True
                            Q.append((next_r, next_c))
        
        count = 0
        for i in range(m):
            for j in range(n):
                if grid[i][j] == '1' and not visited[i][j]:
                    bfs(i, j)
                    count += 1
        return count