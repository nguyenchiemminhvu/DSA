from typing import List

class Solution:
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        mapping = {}
        for i, c in enumerate(order):
            mapping[c] = i
        
        for i in range(1, len(words)):
            arr1 = [mapping[c] for c in words[i - 1]]
            arr2 = [mapping[c] for c in words[i]]
            if arr2 < arr1:
                return False
        return True