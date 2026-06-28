from typing import List

class Solution:
    def maximumElementAfterDecrementingAndRearranging(self, arr: List[int]) -> int:
        arr.sort()

        res = 1
        for i in range(1, len(arr)):
            if res < arr[i]:
                res += 1

        return res