# Algorithm:
    # Start at (rStart, cStart)
    # Add it to result if inside grid
    # Move in spiral:
        # For each direction:
            # Walk step_length steps
            # Add valid cells only
        # Increase step length every 2 turns
    # Stop when collected rows * cols cells

from typing import List

class Solution:
    def spiralMatrixIII(self, m: int, n: int, r_start: int, c_start: int) -> List[List[int]]:
        res = []

        # 4 directions: right, down, left, up
        dir_r = [ 0, 1, 0, -1 ]
        dir_c = [ 1, 0, -1, 0 ]

        r, c = r_start, c_start
        res.append([r, c])

        steps = 1
        while len(res) < m * n:
            for d in range(4):
                dr, dc = dir_r[d], dir_c[d]

                if d == 2:
                    steps += 1
                
                for _ in range(steps):
                    r += dr
                    c += dc
                    if r >= 0 and r < m and c >= 0 and c < n:
                        res.append([r, c])
            steps += 1

        return res