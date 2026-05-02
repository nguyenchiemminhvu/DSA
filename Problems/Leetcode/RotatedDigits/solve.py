class Solution:
    def rotatedDigits(self, n: int) -> int:
        valid = {0, 1, 2, 5, 6, 8, 9}
        change = {2, 5, 6, 9}
        
        def is_good(x):
            has_change = False
            while x:
                d = x % 10
                if d not in valid:
                    return False
                if d in change:
                    has_change = True
                x //= 10
            return has_change
        
        count = 0
        for i in range(1, n + 1):
            if is_good(i):
                count += 1
        
        return count