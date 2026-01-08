from typing import List
from collections import defaultdict

class Solution:
    def topKFrequent(self, words: List[str], top: int) -> List[str]:
        f = defaultdict(int)
        for word in words:
            f[word] += 1
        
        words = list(set(words))
        words.sort(key=lambda x: (-f[x], x))
        return words[:top]