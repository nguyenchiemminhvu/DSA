from typing import List

class Solution:
    def restoreMatrix(self, row_sum: List[int], col_sum: List[int]) -> List[List[int]]:
        m = len(row_sum)
        n = len(col_sum)

        grid = [[0] * n for _ in range(m)]
        i, j = 0, 0
        while i < m and j < n:
            min_val = min(row_sum[i], col_sum[j])
            grid[i][j] += min_val
            row_sum[i] -= min_val
            col_sum[j] -= min_val

            if row_sum[i] == 0:
                i += 1
            else:
                j += 1
        
        return grid