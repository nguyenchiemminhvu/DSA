from typing import List

class Solution:
    def executeInstructions(self, n: int, start: List[int], s: str) -> List[int]:
        dir_map = {
            'L': [0, -1],
            'R': [0,  1],
            'U': [-1, 0],
            'D': [1, 0]
        }

        def test(r, c, s):
            steps = 0
            for ch in s:
                dir_r, dir_c = dir_map[ch]
                nr, nc = r + dir_r, c + dir_c
                if nr >= 0 and nr < n and nc >= 0 and nc < n:
                    r, c = nr, nc
                    steps += 1
                else:
                    break
            return steps
        
        res = []
        for i in range(len(s)):
            r, c = start
            res.append(test(r, c, s[i:]))
        return res