from typing import List, Tuple
from math import floor

class Solution:
    def imageSmoother(self, img: List[List[int]]) -> List[List[int]]:
        def get_smoother_idx(r: int, c: int) -> List[Tuple[int]]:
            return [
                (r - 1, c - 1), (r - 1, c), (r - 1, c + 1),
                (r, c - 1), (r, c), (r, c + 1),
                (r + 1, c - 1), (r + 1, c), (r + 1, c + 1),
            ]
        
        m = len(img)
        n = len(img[0])
        grid = [[0] * n for _ in range(m)]
        for i in range(m):
            for j in range(n):
                idx = get_smoother_idx(i, j)
                s, count = 0, 0
                for r, c in idx:
                    if r >= 0 and r < m and c >= 0 and c < n:
                        s += img[r][c]
                        count += 1
                val = floor(s / count)
                grid[i][j] = val
        return grid