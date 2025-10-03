from typing import List
import unittest

class Solution:
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        # check rows
        for r in range(0, 9):
            s = [0] * 10
            for c in range(0, 9):
                if board[r][c] != '.':
                    val = ord(board[r][c]) - ord('0')
                    s[val] += 1
            s.sort(reverse=True)
            if (s[0] > 1):
                return False

        # check cols
        for c in range(0, 9):
            s = [0] * 10
            for r in range(0, 9):
                if board[r][c] != '.':
                    val = ord(board[r][c]) - ord('0')
                    s[val] += 1
            s.sort(reverse=True)
            if (s[0] > 1):
                return False

        # check boxes
        for r in range(0, 9, 3):
            for c in range(0, 9, 3):
                s = [0] * 10
                for i in range(0,3):
                    for j in range(0, 3):
                        if board[r+i][c+j] != '.':
                            val = ord(board[r+i][c+j]) - ord('0')
                            s[val] += 1
                s.sort(reverse=True)
                if (s[0] > 1):
                    return False

        return True

class TestValidSudoku(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_case_1(self):
        board = [
            ["5","3",".",".","7",".",".",".","."],
            ["6",".",".","1","9","5",".",".","."],
            [".","9","8",".",".",".",".","6","."],
            ["8",".",".",".","6",".",".",".","3"],
            ["4",".",".","8",".","3",".",".","1"],
            ["7",".",".",".","2",".",".",".","6"],
            [".","6",".",".",".",".","2","8","."],
            [".",".",".","4","1","9",".",".","5"],
            [".",".",".",".","8",".",".","7","9"]
        ]
        self.assertTrue(self.solution.isValidSudoku(board))

    def test_case_2(self):
        board = [
            ["8","3",".",".","7",".",".",".","."],
            ["6",".",".","1","9","5",".",".","."],
            [".","9","8",".",".",".",".","6","."],
            ["8",".",".",".","6",".",".",".","3"],
            ["4",".",".","8",".","3",".",".","1"],
            ["7",".",".",".","2",".",".",".","6"],
            [".","6",".",".",".",".","2","8","."],
            [".",".",".","4","1","9",".",".","5"],
            [".",".",".",".","8",".",".","7","9"]
        ]
        self.assertFalse(self.solution.isValidSudoku(board))

if __name__ == "__main__":
    unittest.main()