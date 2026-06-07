class Solution:
    def consecutiveSetBits(self, n: int) -> bool:
        pair = 0b11
        count = 0
        while n:
            check = n & pair
            if check == 0b11:
                count += 1
            n >>= 1
        return count == 1