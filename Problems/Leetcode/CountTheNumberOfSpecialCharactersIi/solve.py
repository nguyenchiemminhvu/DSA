class Solution:
    def numberOfSpecialChars(self, s: str) -> int:
        n = len(s)

        first_upper_idx = {}
        last_lower_idx = {}
        for i in range(n - 1, -1, -1):
            c = s[i]
            if c.isupper():
                first_upper_idx[c.lower()] = i
            elif c not in last_lower_idx:
                last_lower_idx[c] = i
        
        res = 0
        for c in string.ascii_lowercase:
            if c in first_upper_idx and c in last_lower_idx and last_lower_idx[c] < first_upper_idx[c]:
                res += 1
        return res