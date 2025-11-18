from typing import List

class NeighborSum:

    def __init__(self, grid: List[List[int]]):
        self.grid = [[val for val in row] for row in grid]
        self.map = {}
        n = len(grid)
        for r in range(n):
            for c in range(n):
                adj1 = [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]
                s1 = 0
                for nr, nc in adj1:
                    if nr >= 0 and nr < n and nc >= 0 and nc < n:
                        s1 += self.grid[nr][nc]
                
                adj2 = [(r - 1, c - 1), (r - 1, c + 1), (r + 1, c - 1), (r + 1, c + 1)]
                s2 = 0
                for nr, nc in adj2:
                    if nr >= 0 and nr < n and nc >= 0 and nc < n:
                        s2 += self.grid[nr][nc]
                
                self.map[grid[r][c]] = (s1, s2)

    def adjacentSum(self, value: int) -> int:
        return self.map[value][0]

    def diagonalSum(self, value: int) -> int:
        return self.map[value][1]


# Your NeighborSum object will be instantiated and called as such:
# obj = NeighborSum(grid)
# param_1 = obj.adjacentSum(value)
# param_2 = obj.diagonalSum(value)