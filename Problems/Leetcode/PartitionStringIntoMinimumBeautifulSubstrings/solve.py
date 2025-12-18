from typing import List

class Solution:
    def minimumBeautifulSubstrings(self, s: str) -> int:
        def is_power_of_5(val: int) -> bool:
            while val > 1:
                if val % 5 != 0:
                    return False
                val //= 5
            return val == 1
        
        n = len(s)
        count = [float('inf')]
        tmp = []
        def dfs(i: int) -> None:
            if i >= n:
                count[0] = min(count[0], len(tmp))
                return
            for j in range(i, n):
                sub = s[i:j+1]
                if sub[0] == '0':
                    continue
                val = 0
                for c in sub:
                    val = (val << 1) | int(c)
                if is_power_of_5(val):
                    tmp.append(sub)
                    dfs(j + 1)
                    tmp.pop()
        
        dfs(0)
        return -1 if count[0] == 0 or count[0] == float('inf') else count[0]