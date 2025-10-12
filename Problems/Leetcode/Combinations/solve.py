from typing import List

class Solution:
    def combine(self, n: int, k: int) -> List[List[int]]:
        res: List[List[int]] = []
        temp: List[int] = []
        def dfs(i:int, start:int) -> None:
            if i > k:
                res.append([val for val in temp])
                return True
            for val in range(start, n+1):
                temp.append(val)
                if dfs(i + 1, val + 1):
                    pass
                temp.pop()
            return False
        
        if dfs(1, 1):
            print("done")
        return res