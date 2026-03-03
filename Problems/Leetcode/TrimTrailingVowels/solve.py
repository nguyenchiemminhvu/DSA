class Solution:
    def trimTrailingVowels(self, s: str) -> str:
        while len(s) and s[-1] in "aeiou":
            s = s[:-1]
        return s