class Solution:
    def canMakeSubsequence(self, a: str, b: str) -> bool:
        ia, ib = 0, 0
        na, nb = len(a), len(b)
        
        while ia < na and ib < nb:
            if a[ia] == b[ib] or chr((ord(a[ia]) - ord('a') + 1) % 26 + ord('a')) == b[ib]:
                ib += 1
            
            ia += 1
        
        return ib == nb
