from typing import List

class Solution:
    def canMakeArithmeticProgression(self, arr: List[int]) -> bool:
        arr.sort()
        diff = arr[1] - arr[0]
        n = len(arr)
        for i in range(2, n):
            if arr[i] - arr[i - 1] != diff:
                return False
        return True