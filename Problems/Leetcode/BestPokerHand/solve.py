from typing import List
from collections import Counter

class Solution:
    def bestHand(self, ranks: List[int], suits: List[str]) -> str:
        if len(set(suits)) == 1:
            return "Flush"
        
        f = Counter(ranks)
        order = sorted(list(f.values()), reverse=True)
        if order[0] >= 3:
            return "Three of a Kind"
        if order[0] >= 2:
            return "Pair"
        return "High Card"