import string

class Solution:
    def countValidWords(self, s: str) -> int:
        def valid(s: str) -> bool:
            hyphen = 0
            punct = 0
            for i, c in enumerate(s):
                if c.isdigit():
                    return False
                elif c in '!,.':
                    if i != len(s) - 1 or punct > 0:
                        return False
                    punct += 1
                elif c == '-':
                    if hyphen > 0:
                        return False
                    if i == 0 or i == len(s) - 1:
                        return False
                    if not s[i-1].isalpha() or not s[i+1].isalpha():
                        return False
                    hyphen += 1
                elif c.isalpha():
                    continue
                else:
                    return False
            return True
        
        tokens = s.split()
        count = 0
        for token in tokens:
            if valid(token):
                count += 1
        return count