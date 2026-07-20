class Solution:
    def rearrangeString(self, s: str, x: str, y: str) -> str:
        xs = 0
        ys = 0
        t = ''
        for c in s:
            if c == x:
                xs += 1
            elif c == y:
                ys += 1
            else:
                t += c
        t += y * ys
        t += x * xs
        return t