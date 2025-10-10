from typing import List

class Solution:
    def largestLocal(self, grid: List[List[int]]) -> List[List[int]]:
        m = len(grid)
        n = len(grid[0])
        for i in range(0, m - 2):
            for j in range(0, n - 2):
                grid[i][j] = max([grid[i + r][j + c] for r in range(0, 3) for c in range(0, 3)])

        return [grid[i][0:n-2] for i in range(m-2)]