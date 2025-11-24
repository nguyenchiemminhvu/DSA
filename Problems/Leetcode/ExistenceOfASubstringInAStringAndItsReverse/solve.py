class Solution:
    def isSubstringPresent(self, s: str) -> bool:
        rev_s = s[::-1]
        for i in range(1, len(s)):
            if s[i-1:i+1] in rev_s:
                return True
        return False