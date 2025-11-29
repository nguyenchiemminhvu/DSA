from typing import List

class Solution:
    def findKthPositive(self, arr: List[int], k: int) -> int:
        left = 0
        intervals = []
        for val in arr:
            if val > left + 1:
                # missing range is left + 1 -> val - 1
                intervals.append([left + 1, val - 1])
                left = val
            else:
                left = val
        # then add last duration arr[-1] + 1 -> max value 1001
        intervals.append([arr[-1] + 1, arr[-1] + k + 1])

        res = -1
        for left, right in intervals:
            if k <= (right - left) + 1:
                return left + k - 1
            else:
                k -= (right - left) + 1

        return res