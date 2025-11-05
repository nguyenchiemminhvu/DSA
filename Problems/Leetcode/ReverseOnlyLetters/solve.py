import string

class Solution:
    def reverseOnlyLetters(self, s: str) -> str:
        letters = set(string.ascii_uppercase + string.ascii_lowercase)
        temp = []
        for c in s:
            if c in letters:
                temp.append(c)
        temp.reverse()

        s = list(s)
        it = 0
        for i in range(len(s)):
            if s[i] in letters:
                s[i] = temp[it]
                it += 1
        return "".join(s)