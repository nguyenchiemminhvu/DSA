from collections import Counter

class Solution:
    def maxDistance(self, moves: str) -> int:
        c = Counter(moves)        
        return abs(c['U'] - c['D']) + abs(c['L'] - c['R']) + c['_']