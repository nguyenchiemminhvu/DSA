from typing import List

class Solution:
    def maxJump(self, pos: List[int]) -> int:
        n = len(pos)
        if n == 2:
            return pos[-1] - pos[0]

        res = 0
        marked = [False] * n

        prev = 0
        for i in range(2, n, 2):
            res = max(res, pos[i] - pos[prev])
            marked[i] = True
            prev = i
        
        if i != n - 1:
            res = max(res, pos[-1] - pos[i])
            marked[n - 1] = True
            prev = n - 1
        
        for i in range(n - 1, -1, -1):
            if not marked[i]:
                res = max(res, pos[prev] - pos[i])
                marked[i] = True
                prev = i

        return res