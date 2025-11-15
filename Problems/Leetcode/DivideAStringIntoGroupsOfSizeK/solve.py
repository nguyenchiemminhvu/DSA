from typing import List

class Solution:
    def divideString(self, s: str, k: int, fill: str) -> List[str]:
        n = len(s)
        res = []
        for i in range(0, n, k):
            sub = s[i:min(i + k, n)]
            sub += fill * (k - len(sub))
            res.append(sub)
        return res