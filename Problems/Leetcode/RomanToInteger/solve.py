from typing import Dict

class Solution:
    def romanToInt(self, s: str) -> int:
        d: Dict[str, int] = {}
        d['I'] = 1
        d['IV'] = 4
        d['V'] = 5
        d['IX'] = 9
        d['X'] = 10
        d['XL'] = 40
        d['L'] = 50
        d['XC'] = 90
        d['C'] = 100
        d['CD'] = 400
        d['D'] = 500
        d['CM'] = 900
        d['M'] = 1000

        res = 0
        while len(s) > 0:
            if len(s) >= 2 and s[:2] in ['CM', 'CD', 'XC', 'XL', 'IX', 'IV']:
                res += d[s[0:2]]
                s = s[2:]
            else:
                res += d[s[:1]]
                s = s[1:]
        return res