from collections import Counter

class Solution:
    def isScramble(self, s1: str, s2: str) -> bool:
        n = len(s1)

        from functools import cache
        @cache
        def F(i1: int, i2: int, length: int) -> bool:
            if s1[i1:i1 + length] == s2[i2:i2 + length]:
                return True
            
            if Counter(s1[i1:i1 + length]) != Counter(s2[i2:i2 + length]):
                return False

            for sub_len in range(1, length):
                left_len = sub_len
                right_len = length - sub_len

                if F(i1, i2, left_len) and F(i1 + sub_len, i2 + sub_len, right_len):
                    return True
                
                if F(i1, i2 + length - right_len, right_len) and F(i1 + right_len, i2, left_len):
                    return True
            
            return False
        
        return F(0, 0, n)