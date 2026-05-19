from typing import List

class Solution:
    def maxScoreSightseeingPair(self, values: List[int]) -> int:
        n = len(values)

        # res = 0
        # for i in range(n - 1):
        #     for j in range(i + 1, n):
        #         res = max(res, values[i] + i + values[j] - j)
        # return res

        res = 0
        max_val_i = 0
        for i in range(n):
            if i > 0:
                res = max(res, max_val_i + values[i] - i)
            max_val_i = max(max_val_i, values[i] + i)
        return res