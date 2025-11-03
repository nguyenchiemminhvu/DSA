class Solution:
    def licenseKeyFormatting(self, s: str, k: int) -> str:
        s = "".join(s.split('-'))[::-1]
        n = len(s)
        
        groups = []
        for i in range(0, n, k):
            groups.append(s[i:min(i+k, n)])
        return "-".join(groups)[::-1].upper()