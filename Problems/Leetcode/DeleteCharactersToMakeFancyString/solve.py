class Solution:
    def makeFancyString(self, s: str) -> str:
        count = 0
        res = []
        prev = '#'
        for c in s:
            if c == prev:
                count += 1
            else:
                count = 1
            
            if count < 3:
                res.append(c)
            prev = c
        return "".join(res)