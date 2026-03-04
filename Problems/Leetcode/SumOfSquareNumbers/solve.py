from math import sqrt

class Solution:
    def judgeSquareSum(self, c: int) -> bool:
        left = 0
        right = int(sqrt(c)) + 1
        while left <= right:
            s = left ** 2 + right ** 2
            if s == c:
                return True
            if s > c:
                right -= 1
            else:
                left += 1
        
        return False