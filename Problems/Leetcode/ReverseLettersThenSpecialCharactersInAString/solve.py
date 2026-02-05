class Solution:
    def reverseByType(self, s: str) -> str:
        letters = []
        others = []
        for c in s:
            if c.islower():          # or: c in string.ascii_lowercase if strictly a-z
                letters.append(c)
            else:
                others.append(c)

        out = []
        for c in s:
            if c.islower():
                out.append(letters.pop())  # take from end => reversed order
            else:
                out.append(others.pop())
        return "".join(out)