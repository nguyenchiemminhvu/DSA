from typing import List, Dict

class Solution:
    def winningPlayerCount(self, n: int, pick: List[List[int]]) -> int:
        f: Dict[int, Dict[int, int]] = {}
        for p, c in pick:
            if p not in f:
                f[p] = {}
            f[p][c] = f[p].get(c, 0) + 1
        
        players = set([p[0] for p in pick])
        count = 0
        for i, p in enumerate(players):
            print(f[p])
            for k, v in f[p].items():
                if v > p:
                    count += 1
                    break
        return count