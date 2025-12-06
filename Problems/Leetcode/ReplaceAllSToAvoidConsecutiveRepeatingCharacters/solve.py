import string

class Solution:
    def modifyString(self, s: str) -> str:
        s = '#' + s + '#'
        s = list(s)
        res = ""
        n = len(s)
        for i in range(1, n - 1):
            temp = s[i]
            if temp == '?':
                for c in string.ascii_lowercase:
                    if c != s[i - 1] and c != s[i + 1]:
                        temp = c
                        s[i] = temp
                        break
            res += temp
        return res