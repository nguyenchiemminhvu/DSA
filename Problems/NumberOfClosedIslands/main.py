# https://leetcode.com/problems/number-of-closed-islands/

from collections import deque

class Solution:
    def closedIsland(self, grid: List[List[int]]) -> int:
        dir_r = [-1, 1, 0, 0]
        dir_c = [0, 0, -1, 1]

        m, n = len(grid), len(grid[0])
        visited = [[False] * n for _ in range(m)]

        def bfs(r, c):
            Q = deque()
            Q.append((r, c))
            visited[r][c] = True
            res = True
            while Q:
                cur_r, cur_c = Q.popleft()
                if cur_r == 0 or cur_c == 0 or cur_r == m - 1 or cur_c == n - 1:
                    res = False
                for i in range(4):
                    next_r = cur_r + dir_r[i]
                    next_c = cur_c + dir_c[i]
                    if 0 <= next_r < m and 0 <= next_c < n:
                        if grid[next_r][next_c] == 0 and not visited[next_r][next_c]:
                            visited[next_r][next_c] = True
                            Q.append((next_r, next_c))
            return res

        count = 0
        for i in range(1, m - 1):
            for j in range(1, n - 1):
                if grid[i][j] == 0 and not visited[i][j]:
                    if bfs(i, j):
                        count += 1
        return count

if __name__ == "__main__":
    grid = [[1,1,1,1,1,1,1,0],
            [1,0,0,0,0,1,1,0],
            [1,0,1,0,1,1,1,0],
            [1,0,0,0,0,1,0,1],
            [1,1,1,1,1,1,1,0]]
    print(Solution().closedIsland(grid))  # Output: 2
