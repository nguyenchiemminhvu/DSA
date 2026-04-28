from typing import List

class Solution:
    def minOperations(self, grid: List[List[int]], x: int) -> int:
        arr = [val for row in grid for val in row]
        arr.sort()
        n = len(arr)
        for i in range(1, n):
            d = arr[i] - arr[0]
            if d % x != 0:
                return -1
        
        mid = arr[n // 2]
        res = 0
        for val in arr:
            res += abs(val - mid) // x
        return res