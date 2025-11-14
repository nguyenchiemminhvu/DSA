from typing import List

class Solution:
    def mergeArrays(self, a: List[List[int]], b: List[List[int]]) -> List[List[int]]:
        f = {}
        for k, v in a:
            f[k] = f.get(k, 0) + v
        for k, v in b:
            f[k] = f.get(k, 0) + v
        return sorted([[k, v]for k, v in f.items()], key=lambda x: x[0])