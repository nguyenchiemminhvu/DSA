from typing import List

class Solution:
    def partition(self, s: str) -> List[List[str]]:
        n = len(s)
        res = []
        tmp = []
        def dfs(i: int) -> None:
            if i >= n:
                res.append(tmp[:])
                return
            
            for j in range(i, n):
                if s[i:j+1] == s[i:j+1][::-1]:
                    tmp.append(s[i:j+1])
                    dfs(j + 1)
                    tmp.pop()
        
        dfs(0)
        return res