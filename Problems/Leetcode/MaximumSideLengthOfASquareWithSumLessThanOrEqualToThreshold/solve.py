from typing import List

class Solution:
    def maxSideLength(self, mat: List[List[int]], threshold: int) -> int:
        m = len(mat)
        n = len(mat[0])

        def build_prefix_sum() -> List[List[int]]:
            if not mat or not mat[0]:
                return [[0]]
            rows, cols = len(mat), len(mat[0])
            ps = [[0] * (cols + 1) for _ in range(rows + 1)]
            for i in range(rows):
                row_sum = 0
                for j in range(cols):
                    ps[i + 1][j + 1] = mat[i][j] + ps[i][j + 1] + ps[i + 1][j] - ps[i][j]
            return ps
        
        ps = build_prefix_sum()

        def submatrix_sum(ps: List[List[int]], r1: int, c1: int, r2: int, c2: int) -> int:
            return ps[r2 + 1][c2 + 1] - ps[r1][c2 + 1] - ps[r2 + 1][c1] + ps[r1][c1]

        def check_len(k: int) -> bool:
            for i in range(m - k + 1):
                for j in range(n - k + 1):
                    s = submatrix_sum(ps, i, j, i + k - 1, j + k - 1)
                    if s <= threshold:
                        return True
            return False

        res = 0
        left = 1
        right = min(m, n)
        while left <= right:
            mid = left + (right - left) // 2
            if check_len(mid):
                res = mid
                left = mid + 1
            else:
                right = mid - 1
        return res