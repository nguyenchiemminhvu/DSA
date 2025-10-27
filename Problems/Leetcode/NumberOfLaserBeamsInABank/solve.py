from typing import List

class Solution:
    def numberOfBeams(self, bank: List[str]) -> int:
        sum_rows = [row.count('1') for row in bank]

        res = 0
        prev_row = 0
        for i in range(1, len(sum_rows)):
            if sum_rows[i] > 0:
                if i - prev_row > 0:
                    res += (sum_rows[i] * sum_rows[prev_row])
                prev_row = i

        return res