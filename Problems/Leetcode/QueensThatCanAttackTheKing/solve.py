from typing import List

class Solution:
    def queensAttacktheKing(self, queens: List[List[int]], king: List[int]) -> List[List[int]]:
        res = []
        directions = [
            (-1, 0), (1, 0), (0, -1), (0, 1),
            (-1, -1), (-1, 1), (1, -1), (1, 1)
        ]
        s_queen = set()
        for x, y in queens:
            s_queen.add((x, y))

        for dx, dy in directions:
            x, y = king
            while x >= 0 and x < 8 and y >= 0 and y < 8:
                x += dx
                y += dy
                if (x, y) in s_queen:
                    res.append([x, y])
                    break
        
        return res