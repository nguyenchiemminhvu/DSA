from collections import defaultdict

class Solution:
    def countTexts(self, pressed: str) -> int:
        mod = 10**9 + 7

        keys = defaultdict(int)
        for i in range(2, 10):
            keys[str(i)] = 3
        keys['7'] = keys['9'] = 4

        def F(length: int, opts: int) -> int:
            from functools import lru_cache
            @lru_cache(None)
            def dfs(i: int) -> int:
                if i > length:
                    return 0
                if i == length:
                    return 1
                res = 0
                for j in range(1, opts + 1):
                    res += dfs(i + j)
                    res %= mod
                return res
            return dfs(0)
        
        res = 1
        pressed += '#'
        length = 1
        for i in range(1, len(pressed)):
            c = pressed[i]
            if c != pressed[i - 1]:
                res *= F(length, keys[pressed[i - 1]])
                res %= mod
                length = 1
            else:
                length += 1
        
        return res