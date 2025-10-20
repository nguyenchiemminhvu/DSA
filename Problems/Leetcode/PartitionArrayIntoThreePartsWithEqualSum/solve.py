from typing import List

class Solution:
    def canThreePartsEqualSum(self, arr: List[int]) -> bool:
        for i in range(1, len(arr)):
            arr[i] += arr[i - 1]

        if arr[-1] % 3 != 0:
            return False
        
        target = arr[-1] // 3

        try:
            found = arr.index(target)
        except ValueError:
            return False
        
        arr = arr[found + 1:]
        try:
            found = arr.index(target * 2)
        except ValueError:
            return False
        
        return found < (len(arr) - 1)