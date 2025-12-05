import string

class Solution:
    def isValid(self, word: str) -> bool:
        if len(word) < 3:
            return False
        
        count_vowel = 0
        count_cons = 0
        for c in word:
            if  c not in string.ascii_lowercase \
            and c not in string.ascii_uppercase \
            and c not in string.digits:
                return False

            if c in 'AEIOUaeiou':
                count_vowel += 1
            else:
                if c not in string.digits:
                    count_cons += 1
        
        return bool(count_vowel > 0 and count_cons > 0)