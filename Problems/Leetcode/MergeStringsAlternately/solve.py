class Solution:
    def mergeAlternately(self, a: str, b: str) -> str:
        na, nb = len(a), len(b)
        res = [c for p in zip(a, b) for c in p]
        if na < nb:
            res.extend(b[na:])
        else:
            res.extend(a[nb:])
        return "".join(res)