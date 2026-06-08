from math import ceil

class Solution:
    def repeatedStringMatch(self, a: str, b: str) -> int:
        na, nb = len(a), len(b)

        k = math.ceil(nb / na)
        def check(k: int) -> bool:
            temp = a * k
            if b in temp:
                return True
            return False
        
        if check(k):
            return k
        if check(k + 1):
            return k + 1
        return -1