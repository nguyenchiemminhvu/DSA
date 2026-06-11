from collections import defaultdict
from typing import List

class Solution:
    def isPossible(self, n: int, edges: List[List[int]]) -> bool:
        mp = defaultdict(set)
        for u, v in edges:
            mp[u].add(v)
            mp[v].add(u)
        
        odds = [node for node in range(1, n + 1) if len(mp[node]) & 1]

        no = len(odds)
        if no == 0:
            return True
        
        if no == 2:
            a, b = odds
            if b not in mp[a]:
                return True
            for medium in range(1, n + 1):
                if medium != a and medium != b and medium not in mp[a] and medium not in mp[b]:
                    return True
            return False
        
        if no == 4:
            a, b, c, d = odds
            # (a, b) and (c, d)
            if b not in mp[a] and d not in mp[c]:
                return True

            # (a, c) and (b, d)
            if c not in mp[a] and d not in mp[b]:
                return True

            # (a, d) and (b, c)
            if d not in mp[a] and c not in mp[b]:
                return True

            return False

        return False