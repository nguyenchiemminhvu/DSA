from typing import List

class Solution:
    def combinationSum3(self, k: int, target: int) -> List[List[int]]:
        res = []
        arr = [val for val in range(1, 10)]
        n = len(arr)
        nn = (1 << n)
        for mask in range(1, nn):
            tmp = []
            for i in range(n):
                if (1 << i) & mask:
                    tmp.append(arr[i])
            if len(tmp) == k and sum(tmp) == target:
                res.append(tmp[:])
        return res