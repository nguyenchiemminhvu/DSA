class Solution:
    def countPoints(self, rings: str) -> int:
        f = {}
        for i in range(1, len(rings), 2):
            color, pos = rings[i - 1], rings[i]
            if pos not in f:
                f[pos] = set()
            f[pos].add(color)
        return sum(1 for val in f.values() if len(val) == 3)