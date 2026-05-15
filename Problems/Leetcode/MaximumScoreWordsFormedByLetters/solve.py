from typing import List

class Solution:
    def maxScoreWords(self, words: List[str], letters: List[str], score: List[int]) -> int:
        word_counts = []
        word_scores = []
        for word in words:
            freq = [0] * 26
            s = 0
            for c in word:
                idx = ord(c) - ord('a')
                freq[idx] += 1
                s += score[idx]
            word_counts.append(freq)
            word_scores.append(s)
        
        available = [0] * 26
        for letter in letters:
            idx = ord(letter) - ord('a')
            available[idx] += 1
        
        mem = {}
        def F(i: int, remain: tuple[int]) -> int:
            if i >= len(words):
                return 0
            if (i, remain) in mem:
                return mem[(i, remain)]
            
            res = F(i + 1, remain)

            temp_rem = list(remain)
            enough = True
            for j in range(26):
                if word_counts[i][j] > temp_rem[j]:
                    enough = False
                    break
            
            if enough:
                for j in range(26):
                    temp_rem[j] -= word_counts[i][j]
                res = max(res, word_scores[i] + F(i + 1, tuple(temp_rem)))
            
            mem[(i, remain)] = res
            return res
        
        return F(0, tuple(available))