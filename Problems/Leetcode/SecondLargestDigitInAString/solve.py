class Solution:
    def secondHighest(self, s: str) -> int:
        ss = set()
        for c in s:
            if c.isdigit():
                ss.add(int(c))
        if len(ss) < 2:
            return -1
        
        return sorted(list(ss))[-2]