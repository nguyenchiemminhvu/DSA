import string
from collections import Counter

class Solution:
    def robotWithString(self, s: str) -> str:
        counter = Counter(s)
        left = 0
        n = len(s)
        st = []
        res = []
        for c in string.ascii_lowercase:
            while counter[c] > 0 and left < n:
                idx = s.find(c, left, n)
                if idx != -1:
                    for cc in s[left:idx+1]:
                        while st and st[-1] <= c:
                            res.append(st.pop())
                        st.append(cc)
                    left = idx + 1
                    counter[c] -= 1
                else:
                    counter[c] = 0
        while st:
            res.append(st.pop())
        return "".join(res)