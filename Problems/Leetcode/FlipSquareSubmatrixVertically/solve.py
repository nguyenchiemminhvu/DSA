from typing import List

class Solution:
    def reverseSubmatrix(self, grid: List[List[int]], x: int, y: int, k: int) -> List[List[int]]:
        xx, yy = x + k, y + k
        for c in range(y, yy):
            u = x
            d = xx - 1
            while u <= d:
                grid[u][c], grid[d][c] = grid[d][c], grid[u][c]
                u += 1
                d -= 1
        return grid