class Solution:
    def passwordStrength(self, password: str) -> int:
        res = 0
        for c in set(password):
            if c.islower():
                res += 1
            elif c.isupper():
                res += 2
            elif c.isdigit():
                res += 3
            else:
                res += 5
        return res