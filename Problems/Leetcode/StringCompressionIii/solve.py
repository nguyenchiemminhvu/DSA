class Solution:
    def compressedString(self, word: str) -> str:
        n = len(word)

        res = ''
        i = 0
        while i < n:
            c = word[i]
            count = 1
            while i + 1 < n and word[i + 1] == c and count + 1 <= 9:
                count += 1
                i += 1
            
            i += 1
            
            res += str(count) + c
        
        return res