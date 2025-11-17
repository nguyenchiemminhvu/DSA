class Solution:
    def isSumEqual(self, a: str, b: str, t: str) -> bool:
        sa = "".join(str(ord(c) - ord('a')) for c in a)
        sb = "".join(str(ord(c) - ord('a')) for c in b)
        sc = "".join(str(ord(c) - ord('a')) for c in t)
        return int(sa) + int(sb) == int(sc)