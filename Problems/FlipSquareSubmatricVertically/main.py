# https://leetcode.com/problems/flip-square-submatrix-vertically/

from typing import List

class Solution:
    def reverseSubmatrix(self, grid: List[List[int]], x: int, y: int, k: int) -> List[List[int]]:
        xx = x + k - 1
        yy = y + k - 1
        while (x <= xx):
            for i in range(y, yy + 1):
                grid[x][i], grid[xx][i] = grid[xx][i], grid[x][i]
            x += 1
            xx -= 1
        return grid

if __name__ == "__main__":
    solution = Solution()
    grid = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    x, y, k = 0, 0, 3
    result = solution.reverseSubmatrix(grid, x, y, k)
    for row in result:
        print(row)