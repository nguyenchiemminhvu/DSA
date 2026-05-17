from typing import List

class Solution:
    def longestMountain(self, arr: List[int]) -> int:
        n = len(arr)

        up = down = 0
        res = 0
        for i in range(1, n):
            if down > 0 and arr[i] > arr[i - 1]:
                up = down = 0

            if arr[i] > arr[i - 1]:
                up += 1
            elif arr[i] < arr[i - 1]:
                down += 1
            else:
                up = down = 0
            
            if up > 0 and down > 0:
                res = max(res, up + down + 1)
        return res