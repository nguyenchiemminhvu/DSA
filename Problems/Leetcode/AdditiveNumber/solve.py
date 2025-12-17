from typing import List

class Solution:
    def isAdditiveNumber(self, s: str) -> bool:
        n = len(s)
        def dfs(i: int, tmp: List[int]) -> bool:
            if i >= n:
                if len(tmp) <= 2:
                    return False
                return True
            
            for j in range(i, n):
                sub = s[i:j+1]
                if len(sub) > 1 and sub[0] == '0':
                    return False
                val = int(sub)
                if val == tmp[-1] + tmp[-2]:
                    tmp.append(val)
                    if dfs(j + 1, tmp):
                        return True
                    tmp.pop()
            return False
        
        for i in range(1, n):
            for j in range(i + 1, n + 1):
                sa = s[:i]
                sb = s[i:j]
                if (len(sa) > 1 and sa[0] == '0') or (len(sb) > 1 and sb[0] == '0'):
                    continue
                a = int(sa)
                b = int(sb)
                if dfs(j, [a, b]):
                    return True
        return False