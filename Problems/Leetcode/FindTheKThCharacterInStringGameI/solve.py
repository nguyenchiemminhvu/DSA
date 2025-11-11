class Solution:
    def kthCharacter(self, k: int) -> str:
        word = [0]
        n = 1
        while k >= len(word):
            word.extend(word)
            n *= 2
            for i in range(n // 2, n):
                word[i] = (word[i] + 1) % 26
        return chr(ord('a') + word[k - 1])