class Solution:
    def doesAliceWin(self, s: str) -> bool:
        count = 0
        vowel = set('aeiou')
        for c in s:
            if c in vowel:
                count += 1
        
        if count > 0:
            return True
        return False