from typing import List

class Solution:
    def numRookCaptures(self, board: List[List[str]]) -> int:
        r, c = -1, -1
        n = 8
        
        # Find the rook position
        for i in range(n):
            for j in range(n):
                if board[i][j] == 'R':
                    r, c = i, j
                    break
            if r != -1:
                break
        
        count = 0

        # UP
        for i in range(r - 1, -1, -1):
            if board[i][c] == 'B':
                break
            if board[i][c] == 'p':
                count += 1
                break

        # DOWN
        for i in range(r + 1, n):
            if board[i][c] == 'B':
                break
            if board[i][c] == 'p':
                count += 1
                break

        # LEFT
        for j in range(c - 1, -1, -1):
            if board[r][j] == 'B':
                break
            if board[r][j] == 'p':
                count += 1
                break

        # RIGHT
        for j in range(c + 1, n):
            if board[r][j] == 'B':
                break
            if board[r][j] == 'p':
                count += 1
                break

        return count
