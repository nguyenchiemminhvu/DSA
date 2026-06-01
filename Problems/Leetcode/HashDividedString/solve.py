class Solution:
    def stringHash(self, s: str, k: int) -> str:
        res = ''

        n = len(s)
        i = 0
        while i + k <= n:
            sub = s[i:i + k]
            print(sub)
            val = 0
            for c in sub:
                val += (ord(c) - ord('a'))
            val %= 26
            hashed = chr(val + ord('a'))
            res += hashed
            i += k

        return res