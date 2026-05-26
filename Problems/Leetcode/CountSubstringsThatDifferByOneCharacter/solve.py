from collections import deque

class Solution:
    def countSubstrings(self, s: str, t: str) -> int:
        ns, nt = len(s), len(t)
        n = min(ns, nt)

        def comp(s1: str, s2: str) -> bool:
            diff = 0
            for c1, c2 in zip(s1, s2):
                if c1 != c2:
                    diff += 1
            return diff == 1

        count = 0
        for length in range(1, n + 1):
            sub1 = deque()
            for i1 in range(ns):
                sub1.append(s[i1])
                if len(sub1) > length:
                    sub1.popleft()
                if len(sub1) == length:
                    sub2 = deque()
                    for i2 in range(nt):
                        sub2.append(t[i2])
                        if len(sub2) > length:
                            sub2.popleft()
                        if len(sub2) == length:
                            if comp(sub1, sub2):
                                count += 1
        return count