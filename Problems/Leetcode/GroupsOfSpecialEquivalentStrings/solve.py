from collections import defaultdict
from typing import List

class Solution:
    def numSpecialEquivGroups(self, words: List[str]) -> int:
        nw = len(words)
        n = len(words[0])

        f = defaultdict(int)
        for word in words:
            left = []
            right = []
            for i in range(0, n, 2):
                left.append(word[i])
            for i in range(1, n, 2):
                right.append(word[i])
            left.sort()
            right.sort()
            f["".join(left) + "".join(right)] += 1
        
        return len(f)