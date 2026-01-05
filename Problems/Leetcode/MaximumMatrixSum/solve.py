from typing import List

class Solution:
    def maxMatrixSum(self, mat: List[List[int]]) -> int:
        n = len(mat)
        has_zero = False
        count_neg = 0
        sum_non_neg = 0
        min_abs = float('inf')
        for row in mat:
            for val in row:
                if val == 0:
                    has_zero = True
                if val < 0:
                    count_neg += 1
                sum_non_neg += abs(val)
                min_abs = min(min_abs, abs(val))

        if has_zero or count_neg % 2 == 0:
            return sum_non_neg
        return sum_non_neg - 2 * min_abs
