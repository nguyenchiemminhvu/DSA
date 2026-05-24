from typing import List

class Solution:
    def palindromePartition(self, s: str, k: int) -> int:
        n = len(s)
        INF = float('inf')

        def cost(l: int, r: int) -> int:
            changes = 0
            while l <= r:
                if s[l] != s[r]:
                    changes += 1
                l += 1
                r -= 1
            return changes

        mem = {}
        def F(i: int, cnt: int) -> int:
            if i >= n:
                return 0
            if cnt == 1:
                return cost(i, n - 1)
            if (i, cnt) in mem:
                return mem[(i, cnt)]
            res = INF
            for j in range(n - 1, i, -1):
                res = min(
                    res,
                    cost(i, j - 1) + F(j, cnt - 1)
                )
            mem[(i, cnt)] = res
            return res

        return F(0, k)