from collections import defaultdict

class Solution:
    def maxNumberOfBalloons(self, text: str) -> int:
        f = defaultdict(int)
        for c in text:
            f[c] += 1
        
        return min([f['b'], f['a'], f['l'] // 2, f['o'] // 2, f['n']])