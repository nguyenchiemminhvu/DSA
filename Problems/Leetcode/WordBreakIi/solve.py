from typing import List

class Solution:
    def wordBreak(self, s: str, words: List[str]) -> List[str]:
        n = len(s)
        res = []
        def dfs(i: int, temp: List[str]):
            if i > n:
                return
            if i == n:
                res.append(" ".join(temp))
            for word in words:
                nw = len(word)
                if i + nw <= n and s[i:i + nw] == word:
                    temp.append(word)
                    dfs(i + nw, temp)
                    temp.pop()
        dfs(0, [])
        return res