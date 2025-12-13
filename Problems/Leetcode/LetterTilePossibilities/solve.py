from typing import List

class Solution:
    def numTilePossibilities(self, s: str) -> int:
        n = len(s)
        ss = set()
        tmp = []
        visited = [False] * n
        def generating(k: int, idx: int) -> None:
            if idx >= k:
                ss.add("".join(tmp))
                return
            
            for i in range(n):
                if not visited[i]:
                    tmp.append(s[i])
                    visited[i] = True
                    generating(k, idx + 1)
                    visited[i] = False
                    tmp.pop()
        
        for l in range(1, n + 1):
            generating(l, 0)
        return len(ss)