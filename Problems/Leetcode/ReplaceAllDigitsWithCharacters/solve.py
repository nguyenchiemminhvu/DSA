class Solution:
    def replaceDigits(self, s: str) -> str:
        s = list(s)
        for i in range(1, len(s), 2):
            s[i] = chr(ord('a') + ((ord(s[i - 1]) - ord('a') + int(s[i])) % 26))
        return "".join(s)