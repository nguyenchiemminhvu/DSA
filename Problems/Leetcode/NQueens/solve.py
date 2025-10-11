from typing import List

class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        s_row = set()
        s_col = set()
        s_row_add_col = set()
        s_row_sub_col = set()
        table = []
        list_table = []

        def format_table() -> List[str]:
            res = []
            for i in range(n):
                row = ['.'] * n
                row[table[i]] = 'Q'
                res.append("".join(row))
            return res

        def dfs(r) -> None:
            if r == n:
                list_table.append(format_table())
                return
            
            for c in range(0, n):
                if all([r not in s_row, c not in s_col, r + c not in s_row_add_col, r - c not in s_row_sub_col]):
                    # add to set
                    s_row.add(r)
                    s_col.add(c)
                    s_row_add_col.add(r + c)
                    s_row_sub_col.add(r - c)
                    table.append(c)

                    dfs(r + 1)
                    
                    # backtracking, remove from set
                    s_row.remove(r)
                    s_col.remove(c)
                    s_row_add_col.remove(r + c)
                    s_row_sub_col.remove(r - c)
                    table.pop()

        dfs(0)
        return list_table