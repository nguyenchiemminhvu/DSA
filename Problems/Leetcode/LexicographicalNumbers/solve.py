from typing import List

class Solution:
    def lexicalOrder(self, n: int) -> List[int]:
        res = []

        def dfs(base: int):
            if base > n:
                return
            res.append(base)
            for i in range(10):
                dfs(base * 10 + i)
            
        for base in range(1, 10):
            dfs(base)

        return res