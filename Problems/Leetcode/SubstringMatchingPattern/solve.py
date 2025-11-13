class Solution:
    def hasMatch(self, s: str, p: str) -> bool:
        idx = p.find('*')
        p1 = p[0:idx]
        p2 = p[idx + 1:]
        
        found = 0 if p1 == "" else s.find(p1)
        if found == -1:
            return False
        found = s.find(p2, found + len(p1))
        return False if found == -1 else True