from typing import List

class Solution:
    def mapWordWeights(self, words: List[str], weights: List[int]) -> str:
        sums = [(sum(weights[ord(c) - ord('a')] for c in word) % 26) for word in words]
        res = [chr((25 - val) + ord('a')) for val in sums]
        return "".join(res)