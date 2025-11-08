class Solution:
    def canBeTypedWords(self, text: str, brokenLetters: str) -> int:
        banned_keys = set(brokenLetters)
        words = text.split()
        count = 0
        for word in words:
            good = True
            for c in word:
                if c in banned_keys:
                    good = False
                    break
            count += int(good)
        return count