class Solution:
    def longestNiceSubstring(self, s: str) -> str:
        def is_nice(s: str) -> bool:
            s_lower = set()
            s_upper = set()
            for c in s:
                if c.islower():
                    s_lower.add(c)
                else:
                    s_upper.add(c)
            for c in s_lower:
                if c.upper() not in s_upper:
                    return False
            for c in s_upper:
                if c.lower() not in s_lower:
                    return False
            return True

        n = len(s)
        max_len = 0
        selected = ""
        for i in range(n):
            for j in range(i + 1, n):
                if is_nice(s[i:j+1]):
                    if max_len < j - i + 1:
                        max_len = j - i + 1
                        selected = s[i:j + 1]
        return selected