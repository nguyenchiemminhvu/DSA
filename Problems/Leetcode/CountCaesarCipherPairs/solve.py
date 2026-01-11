from typing import List

class Solution:
    def countPairs(self, words: List[str]) -> int:
        n = len(words)
        m = len(words[0])

        count = 0
        f_pattern = {}
        for word in words:
            pattern = []
            for i in range(1, m):
                diff = (ord(word[i]) - ord(word[i - 1])) % 26
                pattern.append(diff)

            if tuple(pattern) in f_pattern:
                count += f_pattern[tuple(pattern)]

            f_pattern[tuple(pattern)] = f_pattern.get(tuple(pattern), 0) + 1
        
        return count