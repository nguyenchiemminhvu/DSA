from typing import List

class Solution:
    def validSequence(self, s1: str, s2: str) -> List[int]:
        n1, n2 = len(s1), len(s2)

        suffix = [0] * (n1 + 1)
        i2 = n2 - 1
        for i1 in range(n1 - 1, -1, -1):
            if i2 >= 0 and s1[i1] == s2[i2]:
                i2 -= 1
            suffix[i1] = n2 - i2 - 1

        res = []
        use_mismatch = False
        i2 = 0
        for i1 in range(n1):
            if i2 == n2:
                break
            
            if s1[i1] == s2[i2]:
                res.append(i1)
                i2 += 1
            else:
                if not use_mismatch:
                    if suffix[i1 + 1] >= n2 - i2 - 1:
                        res.append(i1)
                        i2 += 1
                        use_mismatch = True

        return res if i2 == n2 else []