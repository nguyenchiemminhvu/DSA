class Solution:
    def checkTwoChessboards(self, a: str, b: str) -> bool:
        r, c = int(a[1]), ord(a[0]) - ord('a')
        rr, cc = int(b[1]), ord(b[0]) - ord('a')
        return abs(r - c) & 1 == abs(rr - cc) & 1