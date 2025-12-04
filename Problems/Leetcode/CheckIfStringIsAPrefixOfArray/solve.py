from typing import List

class Solution:
    def isPrefixString(self, s: str, words: List[str]) -> bool:
        start = 0
        n = len(s)
        for word in words:
            if s[start:].startswith(word):
                start += len(word)
            else:
                break
        return start == n