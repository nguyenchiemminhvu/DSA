from typing import List

class Solution:
    def tictactoe(self, moves: List[List[int]]) -> str:
        player = { True: 'X', False: 'O' }
        n = 3
        board = [[' '] * n for _ in range(n)]
        is_first = True
        for r, c in moves:
            board[r][c] = player[is_first]

            # check rows
            for i in range(n):
                if board[i] == [player[is_first]] * n:
                    return 'A' if is_first else 'B'
            
            # check cols
            for i in range(n):
                if [board[0][i], board[1][i], board[2][i]] == [player[is_first]] * n:
                    return 'A' if is_first else 'B'
            
            # check diagonal
            if [board[0][0], board[1][1], board[2][2]] == [player[is_first]] * n:
                return 'A' if is_first else 'B'
            if [board[0][2], board[1][1], board[2][0]] == [player[is_first]] * n:
                return 'A' if is_first else 'B'

            is_first = not is_first

        return "Draw" if len(moves) == 9 else "Pending"