class Solution:
    def getLucky(self, s: str, k: int) -> int:
        temp = 0
        for c in s:
            val = (ord(c) - ord('a')) + 1
            while val:
                temp += (val % 10)
                val //= 10
        
        k -= 1
        while k:
            val = temp
            s = 0
            while val:
                s += (val % 10)
                val //= 10
            temp = s
            k -= 1
        return temp