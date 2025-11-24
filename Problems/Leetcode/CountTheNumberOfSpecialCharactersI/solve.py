class Solution:
    def numberOfSpecialChars(self, word: str) -> int:
        s = set()
        for c in word:
            s.add(c)
        count = 0
        for c in s:
            if c.islower():
                count += int(c.upper() in s)
        return count