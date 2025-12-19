import math
from typing import List

class Solution:
    def minDifference(self, n: int, k: int) -> List[int]:
        def all_div(val: int) -> List[int]:
            divs = []
            s = int(math.sqrt(val) + 1)
            for i in range(1, s):
                if val % i == 0:
                    divs.append(i)
                    if i * i != val:
                        divs.append(val // i)
            divs.sort()
            return divs
        
        divs = all_div(n)
        best_diff = float('inf')
        best_split = []
        tmp = []
        def dfs(i:int, start:int, prod:int) -> None:
            nonlocal best_diff, best_split, tmp
            if i >= k:
                if prod == n:
                    diff = max(tmp) - min(tmp)
                    if diff < best_diff:
                        best_diff = diff
                        best_split = tmp[:]
                return
            
            for j in range(start, len(divs)):
                if prod * divs[j] > n:
                    continue
                tmp.append(divs[j])
                dfs(i + 1, j, prod * divs[j])
                tmp.pop()
        
        dfs(0, 0, 1)
        return best_split
