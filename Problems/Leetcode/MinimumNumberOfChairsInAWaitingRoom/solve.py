class Solution:
    def minimumChairs(self, s: str) -> int:
        n = 0
        cur = 0
        for c in s:
            if c == 'E':
                cur += 1
                n = max(n, cur)
            else:
                cur -= 1
        return n