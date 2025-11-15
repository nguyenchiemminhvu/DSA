from typing import List

class Solution:
    def splitWordsBySeparator(self, words: List[str], sep: str) -> List[str]:
        res = []
        for word in words:
            res.extend(filter(None, word.split(sep)))
        return res