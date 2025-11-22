class Solution:
    def countEven(self, num: int) -> int:
        count = 0
        for val in range(2, num + 1):
            s = 0
            while val:
                s += (val % 10)
                val //= 10
            count += int(not s & 1)
            
        return count