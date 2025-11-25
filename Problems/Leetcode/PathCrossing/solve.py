class Solution:
    def isPathCrossing(self, path: str) -> bool:
        r, c = 0, 0
        s = set()
        move = {
            'N': (-1, 0),
            'S': (1, 0),
            'E': (0, -1),
            'W': (0, 1),
        }

        s.add((r, c))
        for p in path:
            dr, dc = move[p]
            r, c = r + dr, c + dc
            if (r, c) in s:
                return True
            s.add((r, c))
        return False