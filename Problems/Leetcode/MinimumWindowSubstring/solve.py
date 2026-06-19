from collections import defaultdict

class Solution:
    def minWindow(self, s: str, t: str) -> str:
        m, n = len(s), len(t)

        def compare_defaultdicts(d1, d2):
            for k, v in d2.items():
                if k not in d1 or d1[k] < v:
                    return False
            return True

        ft = defaultdict(int)
        for c in t:
            ft[c] += 1
        
        l = 0
        fs = defaultdict(int)
        res = [-1, m]
        for r in range(m):
            fs[s[r]] += 1

            while compare_defaultdicts(fs, ft):
                if r - l < res[1] - res[0]:
                    res = [l, r + 1]
                fs[s[l]] -= 1
                if fs[s[l]] <= 0:
                    fs.pop(s[l])
                l += 1

        return ''if res[1] - res[0] > m else s[res[0]:res[1]]