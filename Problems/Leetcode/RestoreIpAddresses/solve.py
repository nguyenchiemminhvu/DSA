from typing import List

class Solution:
    def restoreIpAddresses(self, s: str) -> List[str]:
        n = len(s)
        res = []
        for i in range(0, n-3):
            for j in range(i + 1, n-2):
                for k in range(j + 1, n-1):
                    l = k + 1
                    a = s[:i + 1]
                    b = s[i + 1:j + 1]
                    c = s[j + 1:k + 1]
                    d = s[k + 1:]
                    tmp = [a, b, c, d]
                    valid = True
                    for sub in tmp:
                        val = int(sub)
                        if val > 255:
                            valid = False
                            break
                        if val > 0 and sub[0] == '0':
                            valid = False
                            break
                        if val == 0 and len(sub) > 1:
                            valid = False
                            break
                    if valid:
                        res.append(".".join(tmp))
        return res