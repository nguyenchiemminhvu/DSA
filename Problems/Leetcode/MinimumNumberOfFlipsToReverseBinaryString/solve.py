class Solution:
    def minimumFlips(self, n: int) -> int:
        rev_n = 0
        temp = n
        while temp:
            rev_n = (rev_n << 1) | (temp & 1)
            temp >>= 1
        
        x = rev_n ^ n
        count = 0
        while x:
            x = x & (x - 1)
            count += 1
        return count