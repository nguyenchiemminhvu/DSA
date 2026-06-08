from typing import List

class Solution:
    def pancakeSort(self, arr: List[int]) -> List[int]:
        n = len(arr)

        res = []
        for i in range(n - 1, 0, -1):
            max_idx = arr.index(max(arr[0:i + 1]))
            if max_idx < i:
                if max_idx != 0:
                    res.append(max_idx + 1)
                    arr[0:max_idx + 1] = arr[0:max_idx + 1][::-1]
                res.append(i + 1)
                arr[0:i + 1] = arr[0:i + 1][::-1]
        return res