from typing import List

class Solution:
    def shiftGrid(self, grid: List[List[int]], k: int) -> List[List[int]]:
        m = len(grid)
        n = len(grid[0])
        arr = [val for row in grid for val in row]
        k %= (m * n)
        arr = (arr[0:m*n - k][::-1] + arr[m*n - k:][::-1])[::-1]
        for i in range(m*n):
            grid[(i // n)][(i % n)] = arr[i]
        return grid