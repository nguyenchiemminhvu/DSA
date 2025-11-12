from typing import List
from collections import Counter
import math

class Solution:
    def hasGroupsSizeX(self, deck: List[int]) -> bool:
        f = Counter(deck)
        x = list(f.values())[0]
        for v in f.values():
            x = math.gcd(x, v)
        return x > 1