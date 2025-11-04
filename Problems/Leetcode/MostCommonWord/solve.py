import re
from typing import List

class Solution:
    def mostCommonWord(self, paragraph: str, banned: List[str]) -> str:
        banned = set(banned)
        words = [word.lower() for word in re.split(r"[!?',; \.]+", paragraph)]
        freq = {}
        cur_max = 0
        cur_str = ""
        for word in words:
            if word not in banned:
                freq[word] = freq.get(word, 0) + 1
                if freq[word] > cur_max:
                    cur_max = freq[word]
                    cur_str = word
        return cur_str