class Solution:
    def arrangeWords(self, text: str) -> str:
        text = text.lower()
        words = text.split()
        words.sort(key=lambda x: len(x))

        words[0] = words[0].capitalize()
        return ' '.join(words)