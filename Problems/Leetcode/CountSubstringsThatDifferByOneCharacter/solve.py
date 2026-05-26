from collections import deque


# Brute-Force O(n^3): enumerate all lengths and all starting positions
class SolutionBruteForce:
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


# Optimal O(n^2): fix the mismatch position, expand left and right
# For each pair (i, j) where s[i] != t[j], count matching chars to the
# left (left) and to the right (right). Each such mismatch contributes
# (left + 1) * (right + 1) valid substring pairs.
class Solution:
    def countSubstrings(self, s: str, t: str) -> int:
        ns, nt = len(s), len(t)
        count = 0

        for i in range(ns):
            for j in range(nt):
                if s[i] != t[j]:
                    # Count matching characters to the left of the mismatch
                    left = 0
                    li, lj = i - 1, j - 1
                    while li >= 0 and lj >= 0 and s[li] == t[lj]:
                        left += 1
                        li -= 1
                        lj -= 1

                    # Count matching characters to the right of the mismatch
                    right = 0
                    ri, rj = i + 1, j + 1
                    while ri < ns and rj < nt and s[ri] == t[rj]:
                        right += 1
                        ri += 1
                        rj += 1

                    count += (left + 1) * (right + 1)

        return count
```