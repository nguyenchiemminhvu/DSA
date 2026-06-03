from typing import List

class SubrectangleQueries:

    def __init__(self, rectangle: List[List[int]]):
        self.grid = rectangle
        self.patches = []

    def updateSubrectangle(self, r: int, c: int, nr: int, nc: int, val: int) -> None:
        self.patches.append((r, c, nr, nc, val))

    def getValue(self, r: int, c: int) -> int:
        np = len(self.patches)
        for i in range(np - 1, -1, -1):
            pr1, pc1, pr2, pc2, val = self.patches[i]
            if r >= pr1 and r <= pr2 and c >= pc1 and c <= pc2:
                return val
        
        return self.grid[r][c]


# Your SubrectangleQueries object will be instantiated and called as such:
# obj = SubrectangleQueries(rectangle)
# obj.updateSubrectangle(row1,col1,row2,col2,newValue)
# param_2 = obj.getValue(row,col)