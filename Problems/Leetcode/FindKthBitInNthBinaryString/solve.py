class Solution:
    def findKthBit(self, n: int, k: int) -> str:
        s = "0"
        for _ in range(2, n + 1):
            inv = ''.join('1' if c == '0' else '0' for c in s)
            s = s + "1" + inv[::-1]
        return s[k - 1]