class Solution:
    def hasSpecialSubstring(self, s: str, k: int) -> bool:
        n = len(s)
        for i in range(n - k + 1):
            sub = s[i:i + k]
            if len(set(sub)) > 1:
                continue
            if i > 0:
                if s[i - 1] == sub[0]:
                    continue
            if i + k < n:
                if s[i + k] == sub[0]:
                    continue
            return True
        return False