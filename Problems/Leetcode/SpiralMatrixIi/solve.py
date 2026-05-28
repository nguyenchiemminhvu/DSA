from typing import List

class Solution:
    def generateMatrix(self, n: int) -> List[List[int]]:
        # right -> down -> left -> up
        dir_r = [ 0, 1, 0, -1 ]
        dir_c = [ 1, 0, -1, 0 ]
        cur_dir = 0

        grid = [[0] * n for _ in range(n)]
        r, c = 0, 0
        cur_val = 1
        while cur_val <= n * n:
            # fill value
            grid[r][c] = cur_val
            cur_val += 1

            # move
            nr = r + dir_r[cur_dir]
            nc = c + dir_c[cur_dir]
            count_turn = 0
            while nr < 0 or nr >= n or nc < 0 or nc >= n or grid[nr][nc] != 0:
                cur_dir = (cur_dir + 1) % 4
                nr = r + dir_r[cur_dir]
                nc = c + dir_c[cur_dir]
                count_turn += 1
                if count_turn > 4:
                    break
            r, c = nr, nc
        
        return grid