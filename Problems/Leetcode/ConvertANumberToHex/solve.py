class Solution:
    def toHex(self, num: int) -> str:
        hex_str = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"]
        signed: bool = False
        if num < 0:
            signed = True
            num = 0xFFFFFFFF + num + 1
        
        if num == 0:
            return "0"

        s = []
        while num > 0:
            val = num & 0xF
            s.append(hex_str[val])
            num >>= 4
        return "".join(reversed(s))