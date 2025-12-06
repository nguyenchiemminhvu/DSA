from typing import List

class Solution:
    def containsPattern(self, arr: List[int], m: int, k: int) -> bool:
        n = len(arr)
        for i in range(n - m + 1):
            sub = arr[i:i+m] * k
            if arr[i:i + m * k] == sub:
                return True
        return False