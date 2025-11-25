class Solution:
    def reformat(self, s: str) -> str:
        a = []
        b = []
        for c in s:
            if c.isdigit():
                a.append(c)
            else:
                b.append(c)
        
        if abs(len(a) - len(b)) > 1:
            return ""
        
        res = ""
        for i in range(min(len(a), len(b))):
            res += a[i] + b[i]
        if len(a) < len(b):
            res = b[-1] + res
        elif len(a) > len(b):
            res += a[-1]
        
        return res