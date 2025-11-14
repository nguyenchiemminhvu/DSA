import string

class Solution:
    def concatHex36(self, n: int) -> str:
        keys = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        
        def to_base(val: int, base: int) -> str:
            s = ""
            while val:
                s += keys[(val % base)]
                val //= base
            return s[::-1]
        
        return to_base(n**2, 16) + to_base(n**3, 36)