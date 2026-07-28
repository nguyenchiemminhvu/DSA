from typing import List

class PrefixMatrix:
    def __init__(self, matrix: List[List[int]]):
        if not matrix or not matrix[0]:
            return
        
        self.rows = len(matrix)
        self.cols = len(matrix[0])
        
        # 1. Initialize an (R+1) x (C+1) prefix matrix with zeros
        self.prefix = [[0] * (self.cols + 1) for _ in range(self.rows + 1)]
        
        # 2. Build the prefix sum matrix
        for r in range(self.rows):
            for c in range(self.cols):
                self.prefix[r + 1][c + 1] = (
                    matrix[r][c] 
                    + self.prefix[r][c + 1]    # Region directly above
                    + self.prefix[r + 1][c]    # Region to the left
                    - self.prefix[r][c]        # Subtract top-left (double counted)
                )

    def sum_region(self, row1: int, col1: int, row2: int, col2: int) -> int:
        return (
            self.prefix[row2 + 1][col2 + 1]  # Complete rectangle from (0,0)
            - self.prefix[row1][col2 + 1]     # Subtract out the top overflow
            - self.prefix[row2 + 1][col1]     # Subtract out the left overflow
            + self.prefix[row1][col1]         # Add back top-left corner (subtracted twice)
        )

class Solution:
    def maxSum(self, grid: List[List[int]]) -> int:
        pre = PrefixMatrix(grid)
        res = 0
        for r in range(2, len(grid)):
            for c in range(2, len(grid[0])):
                s = pre.sum_region(r - 2, c - 2, r, c)
                s -= grid[r - 1][c]
                s -= grid[r - 1][c - 2]
                res = max(res, s)
        return res