from typing import List

class Solution:
    def minimumIndex(self, arr: list[int], target: int) -> int:
        idx = -1
        min_box = float('inf')
        for i in range(len(arr)):
            if arr[i] >= target and arr[i] < min_box:
                min_box = arr[i]
                idx = i
        return idx