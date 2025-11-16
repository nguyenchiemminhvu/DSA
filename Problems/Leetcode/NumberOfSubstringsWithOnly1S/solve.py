class Solution:
    def numSub(self, s: str) -> int:
        res = 0
        s += '0'
        count = 0
        for c in s:
            if c == '0':
                res += (count * (count + 1) // 2) % int(1e9 + 7)
                count = 0
            else:
                count += 1
        return res