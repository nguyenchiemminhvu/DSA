from typing import List

class Solution:
    def splitString(self, s: str) -> bool:
        n = len(s)
        def dfs(i: int, tmp: List[int]) -> bool:
            if i >= n:
                return True
            
            for j in range(i, n):
                sub = s[i:j+1]
                val = int(sub)
                if val == tmp[-1] - 1:
                    tmp.append(val)
                    if dfs(j+1, tmp):
                        return True
                    tmp.pop()
            return False
        
        for i in range(n):
            for j in range(i + 1, n):
                sa = s[:i+1]
                sb = s[i+1:j+1]
                a = int(sa)
                b = int(sb)
                if a == b + 1:
                    if dfs(j + 1, [a, b]):
                        return True
        return False