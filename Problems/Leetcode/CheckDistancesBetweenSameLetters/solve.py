from typing import List

class Solution:
    def checkDistances(self, s: str, distance: List[int]) -> bool:
        fd = {}
        for i, dist in enumerate(distance):
            fd[chr(ord('a') + i)] = dist
        fs = {}
        for i, c in enumerate(s):
            if c not in fs:
                fs[c] = i
            else:
                fs[c] = i - fs[c] - 1
        
        for k, v in fs.items():
            if v != fd[k]:
                return False
        return True