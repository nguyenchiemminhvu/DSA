from typing import List

class Solution:
    def pacificAtlantic(self, heights: List[List[int]]) -> List[List[int]]:
        m = len(heights)
        n = len(heights[0])

        coord_from_p = [[0, 0]]
        coord_from_p.extend([[i, 0] for i in range(1, m)])
        coord_from_p.extend([[0, i] for i in range(1, n)])

        coord_from_a = [[m-1, n-1]]
        coord_from_a.extend([[i, n-1] for i in range(0, m-1)])
        coord_from_a.extend([[m-1, i] for i in range(0, n-1)])

        # directions up down left right
        dir_r = [-1, 1, 0, 0]
        dir_c = [0, 0, -1, 1]
        visited = [[[] for j in range(n)] for i in range(m)]
        def BFS(start_coords:List[List[int]], symbol:str):
            for coord in start_coords:
                visited[coord[0]][coord[1]].append(symbol)
            
            Q = start_coords
            while len(Q) > 0:
                r, c = Q.pop(0)
                
                # traversal 4 directions
                for i in range(0, 4):
                    next_r = r + dir_r[i]
                    next_c = c + dir_c[i]
                    if next_r >= 0 and next_r < m and next_c >= 0 and next_c < n:
                        if symbol not in visited[next_r][next_c]:
                            if heights[next_r][next_c] >= heights[r][c]:
                                visited[next_r][next_c].append(symbol)
                                Q.append([next_r, next_c])
        
        BFS(coord_from_p, 'P')
        BFS(coord_from_a, 'A')

        res = []
        for i in range(m):
            for j in range(n):
                if 'P' in visited[i][j] and 'A' in visited[i][j]:
                    res.append([i, j])

        return res