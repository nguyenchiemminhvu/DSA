from collections import defaultdict
from typing import List

class Solution:
    def findThePrefixCommonArray(self, A: List[int], B: List[int]) -> List[int]:
        n = len(A)
        res = []
        prefix_a = defaultdict(int)
        prefix_b = defaultdict(int)
        common = 0
        for i in range(n):
            a, b = A[i], B[i]
            prefix_a[a] += 1
            prefix_b[b] += 1
            if a == b:
                common += 1
            else:
                if prefix_a[a] == prefix_b[a]:
                    common += 1
                if prefix_a[b] == prefix_b[b]:
                    common += 1
            res.append(common)
        return res