from typing import Dict

class Solution:
    def intToRoman(self, num: int) -> str:
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

        res = ""
        for roman, value in reversed(d.items()):
            while num >= value:
                num -= value
                res += roman
        return res