from typing import List

class Solution:
    def countCharacters(self, words: List[str], chars: str) -> int:
        f_get_idx = lambda x: ord(x) - ord('a')
        f_chars = [0] * 26
        for c in chars:
            f_chars[f_get_idx(c)] += 1
        
        res = 0
        for word in words:
            f_word = [0] * 26
            for c in word:
                f_word[f_get_idx(c)] += 1

            valid = True
            for i in range(26):
                if f_chars[i] < f_word[i]:
                    valid = False
                    break
            if valid:
                res += len(word)
        return res