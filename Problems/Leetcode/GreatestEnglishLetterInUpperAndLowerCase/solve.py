import string

class Solution:
    def greatestLetter(self, s: str) -> str:
        ss = set()
        for c in s:
            ss.add(c)
        for c in string.ascii_lowercase[::-1]:
            if c in ss and c.upper() in ss:
                return c.upper()
        return ""