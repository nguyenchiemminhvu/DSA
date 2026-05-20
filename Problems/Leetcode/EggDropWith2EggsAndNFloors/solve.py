# https://www.geeksforgeeks.org/aptitude/puzzle-set-35-2-eggs-and-100-floors/
class Solution:
    def twoEggDrop(self, n: int) -> int:
        k = 1
        while k * (k - 1) // 2 < n:
            k += 1
        return k - 1