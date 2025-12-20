from typing import List

class Solution:
    def circularPermutation(self, n: int, start: int) -> List[int]:
        arr = []
        for i in range(1 << n):
            arr.append(i ^ (i >> 1))
        
        res = []
        idx = arr.index(start)
        for i in range(idx, idx + (1 << n)):
            res.append(arr[i % (1 << n)])
        return res