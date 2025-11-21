from typing import List

class Solution:
    def trimMean(self, arr: List[int]) -> float:
        n = len(arr)
        arr.sort()
        new_arr = arr[int(5 * n // 100):int(n - (5 * n // 100))]
        new_n = len(new_arr)
        return sum(new_arr) / new_n