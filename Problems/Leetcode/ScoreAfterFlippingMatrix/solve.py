from typing import List

class Solution:
    def matrixScore(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        for r in range(m):
            if grid[r][0] == 0:
                for j in range(n):
                    grid[r][j] = (grid[r][j] + 1) % 2
        
        masks = [0] * m
        for i in range(m):
            if grid[i][0] == 1:
                masks[i] = 1

        for c in range(1, n):
            count_0 = 0
            orig = []
            flip = []
            for r in range(m):
                if grid[r][c] == 0:
                    count_0 += 1
                orig.append(grid[r][c])
                flip.append((grid[r][c] + 1) % 2)
            
            update = orig
            if count_0 > (m // 2):
                update = flip
            
            for i in range(m):
                masks[i] = (masks[i] << 1) | update[i]
        
        return sum(masks)