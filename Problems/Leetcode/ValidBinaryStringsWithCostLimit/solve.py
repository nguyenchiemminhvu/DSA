from typing import List

class Solution:
    def generateValidStrings(self, n: int, k: int) -> list[str]:
        res = []

        def dfs(i: int, cost: int, s: List[str]):
            if cost > k:
                return
            if i >= n:
                res.append(''.join(s))
                return
            for c in '01':
                if s and s[-1] == '1' and c == '1':
                    continue
                dfs(i + 1, cost + (i if c == '1' else 0), s + [c])
        
        dfs(0, 0, [])
        return res