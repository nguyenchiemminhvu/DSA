from typing import List, Set

class Solution:
    def solveSudoku(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        n = 9
        s_row: List[Set[int]] = [set() for _ in range(n)]
        s_col: List[Set[int]] = [set() for _ in range(n)]
        s_box: List[Set[int]] = [set() for _ in range(n)]
        mat = [[(ord(c) - ord('0')) if c.isdigit() else 0 for c in row] for row in board]
        for r in range(n):
            for c in range(n):
                i_box = (r // 3) * 3 + (c // 3)
                if mat[r][c] > 0:
                    s_row[r].add(mat[r][c])
                    s_col[c].add(mat[r][c])
                    s_box[i_box].add(mat[r][c])

        def build_board() -> None:
            for i in range(n):
                for j in range(n):
                    board[i][j] = chr(ord('0') + mat[i][j])

        def dfs(r:int, c:int) -> bool:
            if c == n:
                return dfs(r + 1, 0)
            if r == n:
                build_board()
                return True
            
            cur_val = mat[r][c]
            if cur_val > 0:
                return dfs(r, c + 1)
            else:
                # try to fill the board
                for val in range(1,10):
                    i_box = (r // 3) * 3 + (c // 3)
                    if val in s_row[r] or val in s_col[c] or val in s_box[i_box]:
                        continue

                    prev = mat[r][c]
                    mat[r][c] = val
                    s_row[r].add(val)
                    s_col[c].add(val)
                    s_box[i_box].add(val)
                    if dfs(r, c + 1):
                        return True
                    # backtracking
                    mat[r][c] = prev
                    s_row[r].remove(val)
                    s_col[c].remove(val)
                    s_box[i_box].remove(val)
            return False
        
        if dfs(0, 0):
            print("solved")