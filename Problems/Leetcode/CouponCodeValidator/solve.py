from typing import List
import string

class Solution:
    def validateCoupons(self, code: List[str], businessLine: List[str], isActive: List[bool]) -> List[str]:
        res = []
        lines = ["electronics", "grocery", "pharmacy", "restaurant"]
        words = string.ascii_lowercase + string.ascii_uppercase + string.digits + '_'
        m = {}
        for i in range(len(code)):
            if isActive[i] and businessLine[i] in lines:
                if len(code[i]) > 0 and all(c in words for c in code[i]):
                    if businessLine[i] not in m:
                        m[businessLine[i]] = []
                    m[businessLine[i]].append(code[i])
        for line in lines:
            if line in m:
                m[line].sort()
                res.extend(m[line])
        return res