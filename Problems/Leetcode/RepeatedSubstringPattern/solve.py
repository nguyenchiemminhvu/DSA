class Solution:
    def repeatedSubstringPattern(self, s: str) -> bool:
        if len(s) == 1:
            return False

        sub_n = (len(s) + 1) // 2
        for i in range(1, sub_n + 1):
            if len(s) % i != 0:
                continue
            
            sub = s[0:i]
            times = len(s) // i
            if sub * times == s:
                return True
        return False