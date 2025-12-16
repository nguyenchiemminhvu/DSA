from typing import List

class Solution:
    def numsSameConsecDiff(self, n: int, k: int) -> List[int]:
        res = []
        def dfs(i: int, tmp: List[int]) -> None:
            if i == n - 1:
                num = 0
                for val in tmp:
                    num = num * 10 + val
                res.append(num)
                return
            for val in set([tmp[-1] - k, tmp[-1] + k]):
                if val >= 0 and val <= 9:
                    dfs(i + 1, tmp + [val])
        
        for start in range(1, 10):
            dfs(0, [start])
        return res