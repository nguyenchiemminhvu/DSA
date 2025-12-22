class Solution:
    def mirrorDistance(self, n: int) -> int:
        rev = 0
        temp = n
        while temp:
            rev = rev * 10 + (temp % 10)
            temp //= 10
        return abs(n - rev)