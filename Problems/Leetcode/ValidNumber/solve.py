class Solution:
    def isNumber(self, s: str) -> bool:
        try:
            if all(c not in s for c in '1234567890'):
                return False
            float(s)
        except:
            return False
        return True