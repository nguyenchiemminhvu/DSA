from typing import List

class Solution:
    def floodFill(self, image: List[List[int]], sr: int, sc: int, color: int) -> List[List[int]]:
        m = len(image)
        n = len(image[0])
        orig_color = image[sr][sc]
        visited = [[False for _ in range(n)] for _ in range(m)]
        Q = [(sr, sc)]
        visited[sr][sc] = True
        while len(Q) > 0:
            cur_len = len(Q)
            while cur_len > 0:
                r, c = Q.pop(0)
                cur_len -= 1
                image[r][c] = color

                adj_nodes = [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]
                for node in adj_nodes:
                    next_r, next_c = node
                    if next_r >= 0 and next_r < m and next_c >= 0 and next_c < n:
                        if image[next_r][next_c] == orig_color:
                            if not visited[next_r][next_c]:
                                visited[next_r][next_c] = True
                                Q.append((next_r, next_c))
        return image