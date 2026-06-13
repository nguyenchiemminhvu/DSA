class Solution:
    def reverseWords(self, s: str) -> str:
        words = s.split()
        vowel = set('aeiou')

        count = sum(1 for c in words[0] if c in vowel)
        for i in range(1, len(words)):
            next_count = sum(1 for c in words[i] if c in vowel)
            if next_count == count:
                words[i] = words[i][::-1]
        
        return ' '.join(words)