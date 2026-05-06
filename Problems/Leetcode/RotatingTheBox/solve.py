from typing import List

class Solution:
    def rotateTheBox(self, mat: List[List[str]]) -> List[List[str]]:
        nr = len(mat)
        nc = len(mat[0])
        rotated = [[row[i] for row in mat] for i in range(nc)]
        
        for row in rotated:
            row.reverse()
        
        nr = len(rotated)
        nc = len(rotated[0])
        for c in range(nc):
            move_idx = nr - 1

            for i in range(nr - 1, -1, -1):
                if rotated[i][c] == '*':
                    move_idx = i - 1
                elif rotated[i][c] == '#':
                    rotated[i][c] = '.'
                    rotated[move_idx][c] = '#'
                    move_idx -= 1
        
        return rotated