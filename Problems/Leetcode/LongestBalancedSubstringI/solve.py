from collections import defaultdict

class Solution:
    def longestBalanced(self, s: str) -> int:
        n = len(s)
        res = 0
        for i in range(n):
            counter = defaultdict(int)
            for j in range(i, n):
                counter[s[j]] += 1
                if all(v == counter[s[j]] for v in counter.values()):
                    res = max(res, j - i + 1)
        return res