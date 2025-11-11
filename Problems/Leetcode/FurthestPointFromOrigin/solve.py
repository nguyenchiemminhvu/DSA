class Solution:
    def furthestDistanceFromOrigin(self, moves: str) -> int:
        l, r, u = 0, 0, 0
        for move in moves:
            if move == '_':
                u += 1
            elif move == 'L':
                l += 1
            else:
                r += 1
        return abs(l - r) + u