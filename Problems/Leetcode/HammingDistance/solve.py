class Solution:
    def hammingDistance(self, x: int, y: int) -> int:
        x ^= y
        count = 0
        while x:
            x = x & (x - 1)
            count += 1
        return count