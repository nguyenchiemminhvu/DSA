from typing import List

class Solution:
    def finalPositionOfSnake(self, n: int, commands: List[str]) -> int:
        movement = {}
        movement['UP'] = (-1, 0)
        movement['DOWN'] = (1, 0)
        movement['LEFT'] = (0, -1)
        movement['RIGHT'] = (0, 1)

        r, c = 0, 0
        for com in commands:
            dir_r, dir_c = movement[com]
            r += dir_r
            c += dir_c
        
        return r * n + c