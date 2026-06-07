class Solution:
    def minFlips(self, target: str) -> int:
        flip = 0
        cur = '0'
        for c in target:
            if cur != c:
                flip += 1
                cur = c
        
        return flip