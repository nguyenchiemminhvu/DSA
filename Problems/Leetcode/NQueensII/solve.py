import unittest

class Solution:
    def totalNQueens(self, n: int) -> int:
        s_row = set()
        s_col = set()
        s_row_add_col = set()
        s_row_sub_col = set()

        def dfs(r) -> int:
            if r == n:
                return 1
            
            count = 0
            for c in range(0, n):
                if all([r not in s_row, c not in s_col, r + c not in s_row_add_col, r - c not in s_row_sub_col]):
                    # add to set
                    s_row.add(r)
                    s_col.add(c)
                    s_row_add_col.add(r + c)
                    s_row_sub_col.add(r - c)

                    count += dfs(r + 1)
                    
                    # backtracking, remove from set
                    s_row.remove(r)
                    s_col.remove(c)
                    s_row_add_col.remove(r + c)
                    s_row_sub_col.remove(r - c)

            return count

        return dfs(0)

class TestNQueensII(unittest.TestCase):
    def setUp(self):
        self.sol = Solution()

    def test_example1(self):
        n = 4
        expected_output = 2
        self.assertEqual(self.sol.totalNQueens(n), expected_output)

    def test_example2(self):
        n = 1
        expected_output = 1
        self.assertEqual(self.sol.totalNQueens(n), expected_output)

    def test_no_solution(self):
        n = 3
        expected_output = 0
        self.assertEqual(self.sol.totalNQueens(n), expected_output)

    def test_larger_board(self):
        n = 5
        expected_output = 10
        self.assertEqual(self.sol.totalNQueens(n), expected_output)

if __name__ == "__main__":
    unittest.main()
