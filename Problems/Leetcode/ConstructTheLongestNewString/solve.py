class Solution:
    def longestString(self, x: int, y: int, z: int) -> int:
        return 2 * (z + 2 * min(x, y) + (x != y))