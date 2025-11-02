from typing import List

class Solution:
    def countUnguarded(self, m: int, n: int, guards: List[List[int]], walls: List[List[int]]) -> int:
        grid = [([-1] * n) for _ in range(m)]

        for r,c in walls:
            grid[r][c] = 1
        
        for r,c in guards:
            grid[r][c] = 2
        
        for r in range(m):
            # left -> right
            can_see = False
            for c in range(n):
                if grid[r][c] == 2:
                    can_see = True
                elif grid[r][c] == 1:
                    can_see = False
                else:
                    if can_see:
                        grid[r][c] = 0
            
            # right -> left
            can_see = False
            for c in range(n - 1, -1, -1):
                if grid[r][c] == 2:
                    can_see = True
                elif grid[r][c] == 1:
                    can_see = False
                else:
                    if can_see:
                        grid[r][c] = 0
        
        for c in range(n):
            # top -> bottom
            can_see = False
            for r in range(m):
                if grid[r][c] == 2:
                    can_see = True
                elif grid[r][c] == 1:
                    can_see = False
                else:
                    if can_see:
                        grid[r][c] = 0

            # bottom -> top
            can_see = False
            for r in range(m - 1, -1, -1):
                if grid[r][c] == 2:
                    can_see = True
                elif grid[r][c] == 1:
                    can_see = False
                else:
                    if can_see:
                        grid[r][c] = 0
        
        return sum(row.count(-1) for row in grid)