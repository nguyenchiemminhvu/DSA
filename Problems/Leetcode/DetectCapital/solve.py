class Solution:
    def detectCapitalUse(self, word: str) -> bool:
        if all(c.islower() for c in word) or all(c.isupper() for c in word):
            return True
        
        if word[0].islower():
            return False
        if word[0].isupper():
            return not any(c.isupper() for c in word[1:])
        
        return True