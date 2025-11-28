from typing import List

class Solution:
    def findOcurrences(self, text: str, first: str, second: str) -> List[str]:
        arr = text.split()
        res = []
        for i in range(len(arr)):
            if arr[i] == first and i + 1 < len(arr) and arr[i + 1] == second and i + 2 < len(arr):
                res.append(arr[i + 2])
        return res