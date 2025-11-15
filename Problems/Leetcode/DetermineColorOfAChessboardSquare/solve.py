class Solution:
    def squareIsWhite(self, coord: str) -> bool:
        r, c = int(coord[1]), ord(coord[0]) - ord('a')
        return abs(r - c) % 2 == 0