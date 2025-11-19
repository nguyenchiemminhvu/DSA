class Solution:
    def checkString(self, s: str) -> bool:
        count_b = 0
        for c in s:
            if c == 'b':
                count_b += 1
            else:
                if count_b > 0:
                    return False
        return True