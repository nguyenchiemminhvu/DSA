import string

class Solution:
    def strongPasswordCheckerII(self, password: str) -> bool:
        if len(password) < 8:
            return False
        
        count_low = 0
        count_up = 0
        count_d = 0
        count_spec = 0
        prev = '~'
        for c in password:
            if c == prev:
                return False
            if c in string.ascii_lowercase:
                count_low += 1
            if c in string.ascii_uppercase:
                count_up += 1
            if c in string.digits:
                count_d += 1
            if c in "!@#$%^&*()-+":
                count_spec += 1
            prev = c
        
        if not (count_low >= 1 and count_up >= 1 and count_d >= 1 and count_spec >= 1):
            return False
        
        return True