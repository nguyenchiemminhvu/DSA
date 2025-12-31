class Solution:
    def addMinimum(self, s: str) -> int:
        s = s.replace('abc', '0')
        s = s.replace('ab', '1')
        s = s.replace('bc', '1')
        s = s.replace('ac', '1')
        s = s.replace('a', '2')
        s = s.replace('b', '2')
        s = s.replace('c', '2')

        return sum(int(c) for c in s)