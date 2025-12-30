from typing import List

class Solution:
    def numMagicSquaresInside(self, grid: List[List[int]]) -> int:
        magic_squares = [
            [[8, 1, 6], [3, 5, 7], [4, 9, 2]],
            [[6, 7, 2], [1, 5, 9], [8, 3, 4]],
            [[2, 9, 4], [7, 5, 3], [6, 1, 8]],
            [[4, 3, 8], [9, 5, 1], [2, 7, 6]],
            [[6, 1, 8], [7, 5, 3], [2, 9, 4]],
            [[2, 7, 6], [9, 5, 1], [4, 3, 8]],
            [[4, 9, 2], [3, 5, 7], [8, 1, 6]],
            [[8, 3, 4], [1, 5, 9], [6, 7, 2]],
        ]

        magic_squares_set = {
            tuple(tuple(row) for row in square)
            for square in magic_squares
        }

        m = len(grid)
        n = len(grid[0])
        if m < 3 or n < 3:
            return 0
        
        count = 0
        for i in range(m - 2):
            for j in range(n - 2):
                sub = tuple([tuple(row[j:j + 3]) for row in grid[i:i+3]])
                if sub in magic_squares_set:
                    count += 1
        return count